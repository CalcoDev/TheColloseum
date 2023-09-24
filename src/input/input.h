#ifndef INPUT_H
#define INPUT_H

#include "base/base_bitset.h"
#include "base/base_types.h"

#include "os/os_window.h"

typedef enum I_KeyState
{
  KeyState_Up       = 0x0,
  KeyState_Pressed  = 0x1,
  KeyState_Released = 0x2,
  KeyState_Down     = 0x4
} I_KeyState;

typedef struct I_InputState
{
  Bitset previous_frame;
  Bitset current_frame;
} I_InputState;

I_InputState I_InputStateMake(Arena* arena);

// NOTE(calco): -- Key Helper Functions --
I_KeyState I_InputGetKeyState(I_InputState* input_state, I_Key key);

#endif