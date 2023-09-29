#include "input.h"

#include <stdlib.h>
#include <string.h>
#include <tomlc99/toml.h>

#include "os/os.h"

HashmapImplement(CharPointer, U8);

// TODO(calco): Add error handling
void I_InputMapInit(I_InputMap* input_map, Arena* arena, String8 config_path)
{
  // TODO(calco): Set the input_map all memory to be 0.

  // TODO(calco): Use toml_parse with file contents read from OS_FileRead.
  // String8 file_contents = OS_FileRead(arena, config_path);
  // toml_table_t* root = toml_parse(file_contents.data, err_buf,
  // sizeof(err_buf));

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

  toml_array_t* schemes = toml_array_in(input_map_t, "schemes");
  U32 schemes_l         = toml_array_nelem(schemes);
  for (U64 schemes_i = 0; schemes_i < schemes_l; ++schemes_i)
  {
    toml_table_t* scheme = toml_table_at(schemes, schemes_i);
    {
      toml_datum_t name = toml_string_in(scheme, "name");
      input_map->schemes[schemes_i].name =
          Str8InitArena(arena, name.u.s, strlen(name.u.s));
      free(name.u.s);
    }

    // TODO(calco): Add scheme to ID mapper.
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

    toml_array_t* actions = toml_array_in(ctx, "actions");
    U32 actions_l         = toml_array_nelem(actions);
    for (U64 actions_i = 0; actions_i < actions_l; ++actions_i)
    {
      toml_table_t* action = toml_table_at(actions, actions_i);
      {
        toml_datum_t name = toml_string_in(action, "name");
        toml_datum_t type = toml_string_in(action, "type");

        input_map->contexts[ctxs_i].actions[actions_i].name =
            Str8InitArena(arena, name.u.s, strlen(name.u.s));

        // TODO(calco): Parse action type from string.

        free(name.u.s);
        free(type.u.s);
      }

      toml_array_t* controls = toml_array_in(action, "controls");
      U32 controls_l         = toml_array_nelem(controls);
      for (U64 controls_i = 0; controls_i < controls_l; ++controls_i)
      {
        toml_table_t* control = toml_table_at(controls, controls_i);
        {
          // TODO(calco): Parse schemes based on scheme array

          // TODO(calco): Parse control based on action type
        }
      }
    }

    // TODO(calco): Add context to ID mapper.
  }

  // FINISHED PARSING LOL
  toml_free(root);
}