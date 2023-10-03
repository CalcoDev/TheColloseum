#ifndef INPUT_H
#define INPUT_H

#include "base/base_hashmap.h"
#include "base/base_memory.h"
#include "base/base_string.h"

#define I_INPUTMAP_MAX_SCHEMES                  10
#define I_INPUTMAP_MAX_CONTEXTS                 10
#define I_INPUTMAP_MAX_CONTEXT_ACTIONS          10
#define I_INPUTMAP_MAX_CONTEXT_ACTIONS_CONTROLS 10

HashmapCreatePrototype(CharPointer, U8);

typedef struct I_InputMapScheme
{
  String8 name;
} I_InputMapScheme;

typedef enum I_InputMapContextActionControlType
{
  InputMapContextActionControlType_Null    = 0x0,
  InputMapContextActionControlType_Button  = 0x1,
  InputMapContextActionControlType_Range1D = 0x2,
  InputMapContextActionControlType_Range2D = 0x4
} I_InputMapContextActionControlType;

typedef enum I_InputMapContextActionControlModifier
{
  InputMapContextActionControlModifier_Null     = 0x0,
  InputMapContextActionControlModifier_Pressed  = 0x1,
  InputMapContextActionControlModifier_Held     = 0x2,
  InputMapContextActionControlModifier_Released = 0x4
} I_InputMapContextActionControlModifier;

typedef struct I_InputMapContextActionControl
{
  U8 schemes[I_INPUTMAP_MAX_SCHEMES];
  U8 scheme_count;

  union
  {
    struct _control_button
    {
      U8 key;
      I_InputMapContextActionControlModifier modifier;
    } button;

    struct _control_range1d
    {
      U8 positive_key;
      U8 negative_key;
    } range_1d;

    struct _control_range2d
    {
      U8 up_key;
      U8 down_key;
      U8 left_key;
      U8 right_key;
    } range_2d;
  };
} I_InputMapContextActionControl;

typedef struct I_InputMapContextActionValue
{
  union
  {
    struct _value_button
    {
      U8 value;
      U8 pressed;
      U8 held;
      U8 released;
    } button;

    struct _value_range1d
    {
      U8 value;
    } range_1d;

    struct _value_range2d
    {
      U8 x;
      U8 y;
    } range_2d;
  };
} I_InputMapContextActionValue;

typedef struct I_InputMapContextAction
{
  String8 name;
  I_InputMapContextActionControlType type;
  I_InputMapContextActionValue value;

  I_InputMapContextActionControl
      controls[I_INPUTMAP_MAX_CONTEXT_ACTIONS_CONTROLS];

  U8 control_count;
} I_InputMapContextAction;

typedef struct I_InputMapContext
{
  String8 name;
  B8 active;

  I_InputMapContextAction actions[I_INPUTMAP_MAX_CONTEXT_ACTIONS];
  U8 action_count;

  Hashmap(CharPointer, U8) __action_id_mapper;
} I_InputMapContext;

// TODO(calco): Do away with the strings and instead use IDs under the hood.
typedef struct I_InputMap
{
  String8 name;
  I_InputMapScheme schemes[I_INPUTMAP_MAX_SCHEMES];
  I_InputMapContext contexts[I_INPUTMAP_MAX_CONTEXTS];

  U8 scheme_count;
  U8 context_count;

  U8 active_scheme;

  Hashmap(CharPointer, U8) __scheme_id_mapper;
  Hashmap(CharPointer, U8) __context_id_mapper;
} I_InputMap;

U8 I_InputParseKey(char* data);
void I_InputMapInit(I_InputMap* input_map, Arena* arena, String8 config_path);

void I_InputMapUpdate(I_InputMap* input_map);

/*
General input workflow:
input_map = I_InputMapMake("filepath");

2 ways of interacting:
  a. declare callbacks somehow
  b. get info about something

a. callbacks => a map between action to a callback
  callback_type = (triggered_control) => void;
    where triggered_control contains all control info:
      scheme, type, key, modifiers (flags), positive_keys, negative_keys, up,
down, left, right keys

b. info =>
  => active scheme (get, set)
  => active contexts (get, set, add, remove)
  => action info (get)
  => action control info (get)
*/

I_InputMapScheme* I_InputMapSchemeGetActive(I_InputMap* input_map);
B8 I_InputMapSchemeSetActive(I_InputMap* input_map, char* name);

B8 I_InputMapContextActivate(I_InputMap* input_map, char* name);
B8 I_InputMapContextDectivate(I_InputMap* input_map, char* name);

B8 I_InputMapActionTryGet(
    I_InputMap* input_map, char* ctx_name, char* name,
    I_InputMapContextAction** out
);

#endif