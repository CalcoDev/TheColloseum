#include "input.h"

#include <stdlib.h>
#include <string.h>
#include <tomlc99/toml.h>

#include "base/base_log.h"
#include "os/input/os_input.h"
#include "os/input/os_input_keycodes.h"
#include "os/os.h"

// HashmapImplement(CharPointer, U8);
void HashmapCharPointerToU8Init(
    Arena* arena, HashmapCharPointerToU8* hashmap, U64 exponent,
    HashmapCharPointerToU8Function hashfunction,
    HashmapCharPointerToU8NullElementFunction nullelemfunction,
    HashmapCharPointerToU8EqualElementFunction equalelemfunction
)
{
  hashmap->exponent                = exponent;
  hashmap->bucketcount             = 1 << exponent;
  hashmap->used_buckets            = 0;
  HashmapCharPointerToU8Entry* mem = ArenaPush(
      arena, hashmap->bucketcount * sizeof(HashmapCharPointerToU8Entry)
  );
  hashmap->entries           = mem;
  hashmap->hashfunction      = hashfunction;
  hashmap->nullelemfunction  = nullelemfunction;
  hashmap->equalelemfunction = equalelemfunction;
}
void HashmapCharPointerToU8Add(
    HashmapCharPointerToU8* hashmap, HashmapCharPointerToU8Key key,
    HashmapCharPointerToU8Value value
)
{
  U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);
  HashmapCharPointerToU8Entry entry = {0};
  entry.value                       = value;
  entry.key                         = key;
  U64 i                             = hash;
  while (1)
  {
    i = __HashmapLookup(hash, hashmap->exponent, i);
    if (hashmap->nullelemfunction(hashmap->entries + i))
    {
      if ((U64)hashmap->used_buckets + 1 >= (U64)hashmap->bucketcount)
        return;
      hashmap->used_buckets += 1;
      *(hashmap->entries + i) = entry;
      return;
    }
    else if (hashmap->equalelemfunction(&entry, hashmap->entries + i))
    {
      return;
    }
  }
}
HashmapCharPointerToU8Value HashmapCharPointerToU8Get(
    HashmapCharPointerToU8* hashmap, HashmapCharPointerToU8Key key
)
{
  HashmapCharPointerToU8Entry entry = {0};
  entry.key                         = key;
  U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);
  U64 i    = hash;
  while (1)
  {
    i = __HashmapLookup(hash, hashmap->exponent, i);
    if (hashmap->nullelemfunction(hashmap->entries + i) ||
        hashmap->equalelemfunction(&entry, hashmap->entries + i))
    {
      return (hashmap->entries + i)->value;
    }
  }
}
B32 HashmapCharPointerToU8TryGet(
    HashmapCharPointerToU8* hashmap, HashmapCharPointerToU8Key key,
    HashmapCharPointerToU8Value* outvalue
)
{
  HashmapCharPointerToU8Entry entry = {0};
  entry.key                         = key;
  U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);
  U64 i    = hash;
  while (1)
  {
    i = __HashmapLookup(hash, hashmap->exponent, i);
    if (hashmap->nullelemfunction(hashmap->entries + i))
    {
      return 0;
    }
    else if (hashmap->equalelemfunction(&entry, hashmap->entries + i))
    {
      *outvalue = (hashmap->entries + i)->value;
      return 1;
    }
  }
}

// NOTE(calco): -- HASHMAP KEYS --
// TODO(calco): USE BETTER STRING HASHING FUNCTIONS LMAO
U64 str_hash(CharPointer key, U64 table_size)
{
  uint64_t h  = 0x100;
  int32_t len = strlen(key);
  for (int32_t i = 0; i < len; i++)
  {
    h ^= key[i] & 255;
    h *= 1111111111111111111;
  }
  return h ^ h >> 32;
}

B32 str_null(HashmapEntryPointer(CharPointer, U8) entry)
{
  if (entry->key == '\0' || strlen(entry->key) == 0)
    return 1;

  return 0;
}

B32 str_elem(
    HashmapEntryPointer(CharPointer, U8) e1,
    HashmapEntryPointer(CharPointer, U8) e2
)
{
  B32 both_null = (e1->key == '\0' && e2->key == '\0');
  B32 one_null  = (e1->key == '\0' && e2->key != '\0') ||
                 (e2->key == '\0' && e1->key != '\0');

  if (both_null)
    return 1;
  if (one_null)
    return 0;

  return strcmp(e1->key, e2->key) == 0;
}

static Hashmap(CharPointer, U8) key_mapper;
void init_key_mapper(Arena* arena)
{
  HashmapInit(
      CharPointer, U8, arena, &key_mapper, 9, str_hash, str_null, str_elem
  );

  HashmapAdd(
      CharPointer, U8, &key_mapper, "MouseLeft", OS_Input_MouseButton_Left
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "MouseMiddle", OS_Input_MouseButton_Middle
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "MouseRight", OS_Input_MouseButton_Right
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "LeftArrow", OS_Input_KeyLeftArrow);
  HashmapAdd(CharPointer, U8, &key_mapper, "UpArrow", OS_Input_KeyUpArrow);
  HashmapAdd(
      CharPointer, U8, &key_mapper, "RightArrow", OS_Input_KeyRightArrow
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "DownArrow", OS_Input_KeyDownArrow);
  HashmapAdd(CharPointer, U8, &key_mapper, "Minus", OS_Input_KeyMinus);
  HashmapAdd(CharPointer, U8, &key_mapper, "Equals", OS_Input_KeyEquals);
  HashmapAdd(CharPointer, U8, &key_mapper, "Backspace", OS_Input_KeyBackspace);
  HashmapAdd(CharPointer, U8, &key_mapper, "0", OS_Input_Key0);
  HashmapAdd(CharPointer, U8, &key_mapper, "1", OS_Input_Key1);
  HashmapAdd(CharPointer, U8, &key_mapper, "2", OS_Input_Key2);
  HashmapAdd(CharPointer, U8, &key_mapper, "3", OS_Input_Key3);
  HashmapAdd(CharPointer, U8, &key_mapper, "4", OS_Input_Key4);
  HashmapAdd(CharPointer, U8, &key_mapper, "5", OS_Input_Key5);
  HashmapAdd(CharPointer, U8, &key_mapper, "6", OS_Input_Key6);
  HashmapAdd(CharPointer, U8, &key_mapper, "7", OS_Input_Key7);
  HashmapAdd(CharPointer, U8, &key_mapper, "8", OS_Input_Key8);
  HashmapAdd(CharPointer, U8, &key_mapper, "9", OS_Input_Key9);
  HashmapAdd(CharPointer, U8, &key_mapper, "A", OS_Input_KeyA);
  HashmapAdd(CharPointer, U8, &key_mapper, "B", OS_Input_KeyB);
  HashmapAdd(CharPointer, U8, &key_mapper, "C", OS_Input_KeyC);
  HashmapAdd(CharPointer, U8, &key_mapper, "D", OS_Input_KeyD);
  HashmapAdd(CharPointer, U8, &key_mapper, "E", OS_Input_KeyE);
  HashmapAdd(CharPointer, U8, &key_mapper, "F", OS_Input_KeyF);
  HashmapAdd(CharPointer, U8, &key_mapper, "G", OS_Input_KeyG);
  HashmapAdd(CharPointer, U8, &key_mapper, "H", OS_Input_KeyH);
  HashmapAdd(CharPointer, U8, &key_mapper, "I", OS_Input_KeyI);
  HashmapAdd(CharPointer, U8, &key_mapper, "J", OS_Input_KeyJ);
  HashmapAdd(CharPointer, U8, &key_mapper, "K", OS_Input_KeyK);
  HashmapAdd(CharPointer, U8, &key_mapper, "L", OS_Input_KeyL);
  HashmapAdd(CharPointer, U8, &key_mapper, "M", OS_Input_KeyM);
  HashmapAdd(CharPointer, U8, &key_mapper, "N", OS_Input_KeyN);
  HashmapAdd(CharPointer, U8, &key_mapper, "O", OS_Input_KeyO);
  HashmapAdd(CharPointer, U8, &key_mapper, "P", OS_Input_KeyP);
  HashmapAdd(CharPointer, U8, &key_mapper, "Q", OS_Input_KeyQ);
  HashmapAdd(CharPointer, U8, &key_mapper, "R", OS_Input_KeyR);
  HashmapAdd(CharPointer, U8, &key_mapper, "S", OS_Input_KeyS);
  HashmapAdd(CharPointer, U8, &key_mapper, "T", OS_Input_KeyT);
  HashmapAdd(CharPointer, U8, &key_mapper, "U", OS_Input_KeyU);
  HashmapAdd(CharPointer, U8, &key_mapper, "V", OS_Input_KeyV);
  HashmapAdd(CharPointer, U8, &key_mapper, "W", OS_Input_KeyW);
  HashmapAdd(CharPointer, U8, &key_mapper, "X", OS_Input_KeyX);
  HashmapAdd(CharPointer, U8, &key_mapper, "Y", OS_Input_KeyY);
  HashmapAdd(CharPointer, U8, &key_mapper, "Z", OS_Input_KeyZ);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad0", OS_Input_KeyNumpad0);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad1", OS_Input_KeyNumpad1);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad2", OS_Input_KeyNumpad2);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad3", OS_Input_KeyNumpad3);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad4", OS_Input_KeyNumpad4);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad5", OS_Input_KeyNumpad5);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad6", OS_Input_KeyNumpad6);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad7", OS_Input_KeyNumpad7);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad8", OS_Input_KeyNumpad8);
  HashmapAdd(CharPointer, U8, &key_mapper, "Numpad9", OS_Input_KeyNumpad9);
  HashmapAdd(
      CharPointer, U8, &key_mapper, "NumpadPlus", OS_Input_KeyNumpadPlus
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "NumpadMinus", OS_Input_KeyNumpadMinus
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "NumpadStar", OS_Input_KeyNumpadStar
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "NumpadSlash", OS_Input_KeyNumpadSlash
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "NumpadPeriod", OS_Input_KeyNumpadPeriod
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "LeftShift", OS_Input_KeyLeftShift);
  HashmapAdd(
      CharPointer, U8, &key_mapper, "RightShift", OS_Input_KeyRightShift
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "LeftControl", OS_Input_KeyLeftControl
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "RightControl", OS_Input_KeyRightControl
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "LeftAlt", OS_Input_KeyLeftAlt);
  HashmapAdd(CharPointer, U8, &key_mapper, "RightAlt", OS_Input_KeyRightAlt);
  HashmapAdd(CharPointer, U8, &key_mapper, "CapsLock", OS_Input_KeyCapsLock);
  HashmapAdd(
      CharPointer, U8, &key_mapper, "ScrollLock", OS_Input_KeyScrollLock
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "NumLock", OS_Input_KeyNumLock);
  HashmapAdd(CharPointer, U8, &key_mapper, "Grave", OS_Input_KeyGrave);
  HashmapAdd(CharPointer, U8, &key_mapper, "Enter", OS_Input_KeyEnter);
  HashmapAdd(CharPointer, U8, &key_mapper, "Period", OS_Input_KeyPeriod);
  HashmapAdd(CharPointer, U8, &key_mapper, "Comma", OS_Input_KeyComma);
  HashmapAdd(
      CharPointer, U8, &key_mapper, "ForwardSlash", OS_Input_KeyForwardSlash
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "BackSlash", OS_Input_KeyBackSlash);
  HashmapAdd(CharPointer, U8, &key_mapper, "Semicolon", OS_Input_KeySemicolon);
  HashmapAdd(
      CharPointer, U8, &key_mapper, "Apostrophe", OS_Input_KeyApostrophe
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "OpenBracket", OS_Input_KeyOpenBracket
  );
  HashmapAdd(
      CharPointer, U8, &key_mapper, "CloseBracket", OS_Input_KeyCloseBracket
  );
  HashmapAdd(CharPointer, U8, &key_mapper, "Escape", OS_Input_KeyEscape);
  HashmapAdd(CharPointer, U8, &key_mapper, "Pause", OS_Input_KeyPause);
  HashmapAdd(CharPointer, U8, &key_mapper, "F1", OS_Input_KeyF1);
  HashmapAdd(CharPointer, U8, &key_mapper, "F2", OS_Input_KeyF2);
  HashmapAdd(CharPointer, U8, &key_mapper, "F3", OS_Input_KeyF3);
  HashmapAdd(CharPointer, U8, &key_mapper, "F4", OS_Input_KeyF4);
  HashmapAdd(CharPointer, U8, &key_mapper, "F5", OS_Input_KeyF5);
  HashmapAdd(CharPointer, U8, &key_mapper, "F6", OS_Input_KeyF6);
  HashmapAdd(CharPointer, U8, &key_mapper, "F7", OS_Input_KeyF7);
  HashmapAdd(CharPointer, U8, &key_mapper, "F8", OS_Input_KeyF8);
  HashmapAdd(CharPointer, U8, &key_mapper, "F9", OS_Input_KeyF9);
  HashmapAdd(CharPointer, U8, &key_mapper, "F10", OS_Input_KeyF10);
  HashmapAdd(CharPointer, U8, &key_mapper, "F11", OS_Input_KeyF11);
  HashmapAdd(CharPointer, U8, &key_mapper, "F12", OS_Input_KeyF12);
  HashmapAdd(CharPointer, U8, &key_mapper, "PageUp", OS_Input_KeyPageUp);
  HashmapAdd(CharPointer, U8, &key_mapper, "PageDown", OS_Input_KeyPageDown);
  HashmapAdd(CharPointer, U8, &key_mapper, "End", OS_Input_KeyEnd);
  HashmapAdd(CharPointer, U8, &key_mapper, "Home", OS_Input_KeyHome);
  HashmapAdd(CharPointer, U8, &key_mapper, "Insert", OS_Input_KeyInsert);
  HashmapAdd(CharPointer, U8, &key_mapper, "Delete", OS_Input_KeyDelete);
}

U8 I_InputParseKey(char* data)
{
  U8 index;
  if (HashmapTryGet(CharPointer, U8, &key_mapper, data, &index))
    return index;

  LogFatal(
      "I_InputParseKey received an unknown keycode / could not find its "
      "corresponding index.",
      ""
  );
  return -1;
}

I_InputMapContextActionControlType parse_context_action(char* data)
{
  // TODO(calco): Remove the need for strcmp.
  if (strcmp(data, "button") == 0)
    return InputMapContextActionControlType_Button;
  if (strcmp(data, "range_1d") == 0)
    return InputMapContextActionControlType_Range1D;
  if (strcmp(data, "range_2d") == 0)
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

void parse_context_action_control(
    I_InputMapContextActionControlType type,
    I_InputMapContextActionControl* control, toml_table_t* control_t
)
{
  switch (type)
  {
    case InputMapContextActionControlType_Button:
    {
      toml_datum_t key    = toml_string_in(control_t, "key");
      control->button.key = I_InputParseKey(key.u.s);
      free(key.u.s);

      toml_array_t* modifiers = toml_array_in(control_t, "modifiers");
      U32 modifiers_l         = toml_array_nelem(modifiers);
      for (U64 modifiers_i = 0; modifiers_i < modifiers_l; ++modifiers_i)
      {
        toml_datum_t modifier = toml_string_at(modifiers, modifiers_i);

        I_InputMapContextActionControlModifier mod = 0;
        if (strcmp(modifier.u.s, "pressed") == 0)
          mod = InputMapContextActionControlModifier_Pressed;
        else if (strcmp(modifier.u.s, "released") == 0)
          mod = InputMapContextActionControlModifier_Released;
        else if (strcmp(modifier.u.s, "held") == 0)
          mod = InputMapContextActionControlModifier_Held;
        control->button.modifier |= mod;

        free(modifier.u.s);
      }
      break;
    }
    case InputMapContextActionControlType_Range1D:
    {
      toml_datum_t positive_key = toml_string_in(control_t, "positive_key");
      toml_datum_t negative_key = toml_string_in(control_t, "negative_key");
      control->range_1d.positive_key = I_InputParseKey(positive_key.u.s);
      control->range_1d.negative_key = I_InputParseKey(negative_key.u.s);
      free(positive_key.u.s);
      free(negative_key.u.s);
      break;
    }
    case InputMapContextActionControlType_Range2D:
    {
      toml_datum_t right          = toml_string_in(control_t, "right_key");
      toml_datum_t up             = toml_string_in(control_t, "up_key");
      toml_datum_t left           = toml_string_in(control_t, "left_key");
      toml_datum_t down           = toml_string_in(control_t, "down_key");
      control->range_2d.right_key = I_InputParseKey(right.u.s);
      control->range_2d.up_key    = I_InputParseKey(up.u.s);
      control->range_2d.left_key  = I_InputParseKey(left.u.s);
      control->range_2d.down_key  = I_InputParseKey(down.u.s);
      free(right.u.s);
      free(up.u.s);
      free(left.u.s);
      free(down.u.s);
      break;
    }
    default:
    {
      LogFatal(
          "parse_context_action_control received unknown action control type!",
          ""
      );
      break;
    }
  }
}

// TODO(calco): Add error handling
void I_InputMapInit(I_InputMap* input_map, Arena* arena, String8 config_path)
{
  // INITI THE INPUT MAP
  HashmapInit(
      CharPointer, U8, arena, &input_map->__scheme_id_mapper, 7, str_hash,
      str_null, str_elem
  );

  HashmapInit(
      CharPointer, U8, arena, &input_map->__context_id_mapper, 7, str_hash,
      str_null, str_elem
  );

  char err_buf[256];

  TempArena _temp_arena = ArenaBeginTemp(arena);
  String8 file_contents = OS_FileRead(arena, config_path);
  toml_table_t* root = toml_parse(file_contents.data, err_buf, sizeof(err_buf));
  ArenaEndTempSetZero(&_temp_arena);

  init_key_mapper(arena);

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

  toml_array_t* ctxs       = toml_array_in(input_map_t, "contexts");
  U32 ctxs_l               = toml_array_nelem(ctxs);
  input_map->context_count = ctxs_l;
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
    HashmapInit(
        CharPointer, U8, arena, &input_map->contexts[ctxs_i].__action_id_mapper,
        7, str_hash, str_null, str_elem
    );
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

          parse_context_action_control(
              input_map->contexts[ctxs_i].actions[actions_i].type,
              &input_map->contexts[ctxs_i]
                   .actions[actions_i]
                   .controls[controls_i],
              control
          );
        }
      }

      HashmapAdd(
          CharPointer, U8, &input_map->contexts[ctxs_i].__action_id_mapper,
          input_map->contexts[ctxs_i].actions[actions_i].name.data, actions_i
      );
    }

    HashmapAdd(
        CharPointer, U8, &input_map->__context_id_mapper,
        input_map->contexts[ctxs_i].name.data, ctxs_i
    );
  }

  // FINISHED PARSING LOL
  toml_free(root);
}

void I_InputMapUpdate(I_InputMap* input_map)
{
  for (U64 ctx_i = 0; ctx_i < input_map->context_count; ++ctx_i)
  {
    I_InputMapContext* ctx = &input_map->contexts[ctx_i];
    for (U64 act_i = 0; act_i < ctx->action_count; ++act_i)
    {
      I_InputMapContextAction* act = &ctx->actions[act_i];
      switch (act->type)
      {
        case InputMapContextActionControlType_Button:
        {
          U8 value = 0;
          U8 p = 0, r = 0, h = 0;

          for (U64 ctrl_i = 0; ctrl_i < act->control_count; ++ctrl_i)
          {
            I_InputMapContextActionControl* ctrl = &act->controls[ctrl_i];

            B8 valid = 0;
            for (U64 sch_i = 0; sch_i < ctrl->scheme_count; ++sch_i)
            {
              valid |= (input_map->active_scheme == ctrl->schemes[sch_i]);
              if (valid)
                break;
            }

            if (!valid)
              continue;

            B8 is_mouse = ctrl->button.key < 5;
            B8 pressed  = is_mouse ? OS_InputButtonPressed(ctrl->button.key)
                                   : OS_InputKeyPressed(ctrl->button.key);
            B8 released = is_mouse ? OS_InputButtonReleased(ctrl->button.key)
                                   : OS_InputKeyReleased(ctrl->button.key);
            B8 held     = is_mouse ? OS_InputButton(ctrl->button.key)
                                   : OS_InputKey(ctrl->button.key);
            p |= pressed;
            r |= released;
            h |= held;
            I_InputMapContextActionControlModifier mod = ctrl->button.modifier;
            if (mod & InputMapContextActionControlModifier_Pressed)
              value |= pressed;
            if (mod & InputMapContextActionControlModifier_Released)
              value |= released;
            if (mod & InputMapContextActionControlModifier_Held)
              value |= held;
          }

          act->value.button.value    = value;
          act->value.button.pressed  = p;
          act->value.button.released = r;
          act->value.button.held     = h;
          break;
        }
        case InputMapContextActionControlType_Range1D:
        {
          F32 value = 0.f;

          for (U64 ctrl_i = 0; ctrl_i < act->control_count; ++ctrl_i)
          {
            I_InputMapContextActionControl* ctrl = &act->controls[ctrl_i];

            B8 valid = 0;
            for (U64 sch_i = 0; sch_i < ctrl->scheme_count; ++sch_i)
            {
              valid |= (input_map->active_scheme == ctrl->schemes[sch_i]);
              if (valid)
                break;
            }

            if (!valid)
              continue;

            value += (F32)OS_InputKey(ctrl->range_1d.positive_key) -
                     (F32)OS_InputKey(ctrl->range_1d.negative_key);
          }
          act->value.range_1d.value = value;
          break;
        }
        case InputMapContextActionControlType_Range2D:
        {
          F32 x_value = 0.f;
          F32 y_value = 0.f;

          for (U64 ctrl_i = 0; ctrl_i < act->control_count; ++ctrl_i)
          {
            I_InputMapContextActionControl* ctrl = &act->controls[ctrl_i];

            B8 valid = 0;
            for (U64 sch_i = 0; sch_i < ctrl->scheme_count; ++sch_i)
            {
              valid |= (input_map->active_scheme == ctrl->schemes[sch_i]);
              if (valid)
                break;
            }

            if (!valid)
              continue;

            x_value += (F32)OS_InputKey(ctrl->range_2d.right_key) -
                       (F32)OS_InputKey(ctrl->range_2d.left_key);
            y_value += (F32)OS_InputKey(ctrl->range_2d.up_key) -
                       (F32)OS_InputKey(ctrl->range_2d.down_key);
          }
          act->value.range_2d.x = x_value;
          act->value.range_2d.y = y_value;
          break;
        }
        default:
          break;
      }
    }
  }
}

I_InputMapScheme* I_InputMapSchemeGetActive(I_InputMap* input_map)
{
  return &(input_map->schemes[input_map->active_scheme]);
}

B8 I_InputMapSchemeSetActive(I_InputMap* input_map, char* name)
{
  U8 id;
  if (HashmapTryGet(CharPointer, U8, &input_map->__scheme_id_mapper, name, &id))
  {
    input_map->active_scheme = id;
    return 1;
  }

  return 0;
}

B8 I_InputMapContextActivate(I_InputMap* input_map, char* name)
{
  U8 id;
  B8 found = HashmapTryGet(
      CharPointer, U8, &input_map->__context_id_mapper, name, &id
  );

  if (found)
  {
    input_map->contexts[id].active = 1;
    return 1;
  }

  return 0;
}

B8 I_InputMapContextDectivate(I_InputMap* input_map, char* name)
{
  U8 id;
  B8 found = HashmapTryGet(
      CharPointer, U8, &input_map->__context_id_mapper, name, &id
  );

  if (found)
  {
    input_map->contexts[id].active = 0;
    return 1;
  }

  return 0;
}

B8 I_InputMapActionTryGet(
    I_InputMap* input_map, char* ctx_name, char* name,
    I_InputMapContextAction** out
)
{
  U8 ctx_id;
  B8 ctx_found = HashmapTryGet(
      CharPointer, U8, &input_map->__context_id_mapper, ctx_name, &ctx_id
  );
  if (!ctx_found)
    return 0;

  U8 act_id;
  B8 act_found = HashmapTryGet(
      CharPointer, U8, &input_map->contexts[ctx_id].__action_id_mapper, name,
      &act_id
  );
  if (!act_found)
    return 0;

  *out = &input_map->contexts[ctx_id].actions[act_id];
  return 1;
}