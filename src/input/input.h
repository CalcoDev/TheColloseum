#ifndef INPUT_H
#define INPUT_H

#include "base/base_hashmap.h"
#include "base/base_memory.h"
#include "base/base_string.h"

#define I_INPUTMAP_MAX_SCHEMES                  10
#define I_INPUTMAP_MAX_CONTEXTS                 10
#define I_INPUTMAP_MAX_CONTEXT_ACTIONS          10
#define I_INPUTMAP_MAX_CONTEXT_ACTIONS_CONTROLS 10

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
  I_InputMapScheme* scheme;

  union
  {
    struct
    {
      U32 key;
      I_InputMapContextActionControlModifier modifier;
    };

    struct
    {
      U32 positive_key;
      U32 negative_key;
    }

    struct
    {
      U32 up_key;
      U32 down_key;
      U32 left_key;
      U32 right_key;
    }
  };
} I_InputMapContextActionControl;

typedef struct I_InputMapContextAction
{
  String8 name;
  I_InputMapContextActionControlType type;

  I_InputMapContextActionControl
      controls[I_INPUTMAP_MAX_CONTEXT_ACTIONS_CONTROLS];
} I_InputMapContextAction;

typedef struct I_InputMapContext
{
  String8 name;
  I_InputMapContextAction actions[I_INPUTMAP_MAX_CONTEXT_ACTIONS];

  // Hashmap(char*, U64) __actionsIdMapper;
} I_InputMapContext;

// TODO(calco): Do away with the strings and instead use IDs under the hood.
typedef struct I_InputMap
{
  String8 name;
  I_InputMapScheme schemes[I_INPUTMAP_MAX_SCHEMES];
  I_InputMapContext contexts[I_INPUTMAP_MAX_CONTEXTS];

  U8 active_scheme;
  U8 active_contexts[I_INPUTMAP_MAX_CONTEXTS];
} I_InputMap;

void I_InputMapInit(I_InputMap* input_map, Arena* arena, String8 config_path);

#endif