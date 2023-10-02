#include "input.h"

#include <stdlib.h>
#include <string.h>
#include <tomlc99/toml.h>

#include "base/base_log.h"
#include "os/os.h"

HashmapImplement(CharPointer, U8);

I_InputMapContextActionControlType parse_context_action(char* data)
{
  // TODO(calco): Remove the need for strcmp.
  if (strcmp(data, "button"))
    return InputMapContextActionControlType_Button;
  if (strcmp(data, "range_1d"))
    return InputMapContextActionControlType_Range1D;
  if (strcmp(data, "range_2d"))
    return InputMapContextActionControlType_Range2D;

  LogFatal("parse_context_action received an unknown action control type.", "");
  return InputMapContextActionControlType_Null;
}

/**
 * @brief Returns the index of the corresponding action scheme
 * @param input_map The input map to check for schemes in
 * @param data The string to check
 * @return
 */
U8 parse_context_action_scheme(I_InputMap* input_map, char* data)
{
  // TODO(calco): Remove the need for strcmp.
  U8 id = -1;
  if (HashmapTryGet(CharPointer, U8, &input_map->__scheme_id_mapper, data, &id))
    return id;

  LogFatal(
      "parse_context_action_scheme could not find corresponding action scheme.",
      ""
  );
  return -1;
}

// TODO(calco): Conver to String8 instead of charpointer
U64 str_hash(CharPointer key, U64 table_size)
{
  U64 hash   = 5381;
  U64 offset = 0;
  U8 c;

  U64 size = strlen(key);
  while (offset < size)
  {
    c      = *(key + offset);
    hash   = ((hash << 5) + hash) + c;
    offset = offset + 1;
  }

  return hash % table_size;
}

B32 str_null(HashmapEntry(CharPointer, U8) entry)
{
  if (strlen(entry.key) == 0)
    return 1;

  return 0;
}

// TODO(calco): Add error handling
void I_InputMapInit(I_InputMap* input_map, Arena* arena, String8 config_path)
{
  // TODO(calco): Use toml_parse with file contents read from OS_FileRead.
  // String8 file_contents = OS_FileRead(arena, config_path);
  // toml_table_t* root = toml_parse(file_contents.data, err_buf,
  // sizeof(err_buf));

  // INITI THE INPUT MAP
  HashmapInit(
      CharPointer, U8, arena, &input_map->__scheme_id_mapper,
      I_INPUTMAP_MAX_SCHEMES * 4, str_hash, str_null
  );

  FILE* f = fopen(config_path.data, "r");
  char err_buf[256];
  toml_table_t* root = toml_parse_file(f, err_buf, sizeof(err_buf));
  fclose(f);

  toml_table_t* input_map_t = toml_table_in(root, "input_map");
  {
    toml_datum_t name = toml_string_in(input_map_t, "name");
    input_map->name   = Str8InitArena(arena, name.u.s, strlen(name.u.s));
    free(name.u.s);
  }

  toml_array_t* schemes   = toml_array_in(input_map_t, "schemes");
  U32 schemes_l           = toml_array_nelem(schemes);
  input_map->scheme_count = schemes_l;
  for (U64 schemes_i = 0; schemes_i < schemes_l; ++schemes_i)
  {
    toml_table_t* scheme = toml_table_at(schemes, schemes_i);
    {
      toml_datum_t name = toml_string_in(scheme, "name");
      input_map->schemes[schemes_i].name =
          Str8InitArena(arena, name.u.s, strlen(name.u.s));
      free(name.u.s);
    }

    HashmapAdd(
        CharPointer, U8, &input_map->__scheme_id_mapper,
        input_map->schemes[schemes_i].name.data, schemes_i
    );
  }

  toml_array_t* ctxs = toml_array_in(input_map_t, "contexts");
  U32 ctxs_l         = toml_array_nelem(ctxs);
  for (U64 ctxs_i = 0; ctxs_i < ctxs_l; ++ctxs_i)
  {
    toml_table_t* ctx = toml_table_at(ctxs, ctxs_i);
    {
      toml_datum_t name = toml_string_in(ctx, "name");
      input_map->contexts[ctxs_i].name =
          Str8InitArena(arena, name.u.s, strlen(name.u.s));
      free(name.u.s);
    }

    toml_array_t* actions                    = toml_array_in(ctx, "actions");
    U32 actions_l                            = toml_array_nelem(actions);
    input_map->contexts[ctxs_i].action_count = actions_l;
    for (U64 actions_i = 0; actions_i < actions_l; ++actions_i)
    {
      toml_table_t* action = toml_table_at(actions, actions_i);
      {
        toml_datum_t name = toml_string_in(action, "name");
        toml_datum_t type = toml_string_in(action, "type");

        input_map->contexts[ctxs_i].actions[actions_i].name =
            Str8InitArena(arena, name.u.s, strlen(name.u.s));

        input_map->contexts[ctxs_i].actions[actions_i].type =
            parse_context_action(type.u.s);

        free(name.u.s);
        free(type.u.s);
      }

      toml_array_t* controls = toml_array_in(action, "controls");
      U32 controls_l         = toml_array_nelem(controls);
      input_map->contexts[ctxs_i].actions[actions_i].control_count = controls_l;
      for (U64 controls_i = 0; controls_i < controls_l; ++controls_i)
      {
        toml_table_t* control = toml_table_at(controls, controls_i);
        {
          // TODO(calco): Parse schemes based on scheme array
          {
            toml_array_t* ct_schemes = toml_array_in(control, "schemes");
            U32 ct_schemes_l         = toml_array_nelem(ct_schemes);
            input_map->contexts[ctxs_i]
                .actions[actions_i]
                .controls[controls_i]
                .scheme_count = ct_schemes_l;
            for (U64 ct_schemes_i = 0; ct_schemes_i < ct_schemes_l;
                 ++ct_schemes_i)
            {
              toml_datum_t ct_scheme = toml_string_at(ct_schemes, ct_schemes_i);

              input_map->contexts[ctxs_i]
                  .actions[actions_i]
                  .controls[controls_i]
                  .schemes[ct_schemes_i] =
                  parse_context_action_scheme(input_map, ct_scheme.u.s);

              free(ct_scheme.u.s);
            }
          }

          // TODO(calco): Parse control based on action type
        }
      }
    }

    // TODO(calco): Add context to ID mapper.
  }
  input_map->context_count = ctxs_l;

  // FINISHED PARSING LOL
  toml_free(root);
}