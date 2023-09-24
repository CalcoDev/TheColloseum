#include "input.h"

I_InputState I_InputStateMake(Arena* arena)
{
  I_InputState state = {0};

  state.previous_frame = BitsetMakeArenaSize(arena, Key_MAX);
  state.current_frame  = BitsetMakeArenaSize(arena, Key_MAX);

  return state;
}

void wrapper_WindowKeyCallback(
    OS_Window* window, U32 key, OS_WindowKeyAction action
)
{
}

I_KeyState I_InputGetKeyState(I_InputState* input_state, I_Key key)
{
  U8 prev = BitsetGet(&input_state->previous_frame, (U64)key);
  U8 curr = BitsetGet(&input_state->current_frame, (U64)key);

  if (prev && curr)
    return KeyState_Down;
  if (!prev && curr)
    return KeyState_Pressed;
  if (!prev && !curr)
    return KeyState_Up;
  if (prev && !curr)
    return KeyState_Released;
}