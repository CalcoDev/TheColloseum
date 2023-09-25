/*
MOST OF THE CODE HERE WAS TAKEN AND ONLY SLIGHTLY CHANGED FROM
https://github.com/PixelRifts/c-codebase/tree/master
*/

#include "os_input.h"

// Used only in implementation, to store stuff lol
typedef struct __OS_InputState
{
  // TODO(calco): These should be bitmaps.
  U8 key_frame_states[350];
  U8 key_current_states[350];
  U8 button_frame_states[8];
  U8 button_current_states[8];

  F32 mouse_x;
  F32 mouse_y;
  F32 mouse_scrollx;
  F32 mouse_scrolly;
  F32 mouse_absscrollx;
  F32 mouse_absscrolly;
  F32 mouse_recordedx;
  F32 mouse_recordedy;
} __OS_InputState;
static __OS_InputState _state;

void __OS_InputKeyCallback(U8 key, S32 action)
{
  switch (action)
  {
    case OS_Input_Press:
    {
      _state.key_frame_states[key]   = 0b00000001;
      _state.key_current_states[key] = 1;
    }
    break;

    case OS_Input_Release:
    {
      _state.key_frame_states[key]   = 0b00000010;
      _state.key_current_states[key] = 0;
    }
    break;

    case OS_Input_Repeat:
    {
      _state.key_frame_states[key] = 0b00000100;
    }
    break;
  }
}

B8 __OS_InputKeyCallbackCheckRepeat(U8 key, S32 action)
{
  B8 did_repeat = 0;
  if (action == OS_Input_Press)
  {
    if (_state.key_current_states[key] == 1)
    {
      action     = OS_Input_Repeat;
      did_repeat = 1;
    }
  }

  switch (action)
  {
    case OS_Input_Press:
    {
      _state.key_frame_states[key]   = 0b00000001;
      _state.key_current_states[key] = 1;
    }
    break;

    case OS_Input_Release:
    {
      _state.key_frame_states[key]   = 0b00000010;
      _state.key_current_states[key] = 0;
    }
    break;

    case OS_Input_Repeat:
    {
      _state.key_frame_states[key] = 0b00000100;
    }
    break;
  }

  return did_repeat;
}

void __OS_InputButtonCallback(U8 button, S32 action)
{
  if (button < 0 || button >= 8)
    return;

  switch (action)
  {
    case OS_Input_Press:
    {
      _state.button_frame_states[button]   = 0b00000001;
      _state.button_current_states[button] = 1;
      _state.mouse_recordedx               = _state.mouse_x;
      _state.mouse_recordedy               = _state.mouse_y;
    }
    break;
    case OS_Input_Release:
    {
      _state.button_frame_states[button]   = 0b00000010;
      _state.button_current_states[button] = 0;
      _state.mouse_recordedx               = _state.mouse_x;
      _state.mouse_recordedy               = _state.mouse_y;
    }
    break;
  }
}

void __OS_InputCursorPosCallback(F32 xpos, F32 ypos)
{
  _state.mouse_x = xpos;
  _state.mouse_y = ypos;
}

void __OS_InputScrollCallback(F32 xscroll, F32 yscroll)
{
  _state.mouse_scrollx = xscroll;
  _state.mouse_scrolly = yscroll;
  _state.mouse_absscrollx += xscroll;
  _state.mouse_absscrolly += yscroll;
}

void __OS_InputReset(void)
{
  memset(_state.key_frame_states, 0, 350 * sizeof(U8));
  memset(_state.button_frame_states, 0, 8 * sizeof(U8));
  _state.mouse_scrollx = 0;
  _state.mouse_scrolly = 0;
}

B32 OS_InputKey(U8 key) { return _state.key_current_states[key]; }
B32 OS_InputKeyPressed(U8 key)
{
  return (_state.key_frame_states[key] == 0b00000001);
}
B32 OS_InputKeyReleased(U8 key)
{
  return (_state.key_frame_states[key] == 0b00000010);
}
B32 OS_InputKeyHeld(U8 key)
{
  return (_state.key_frame_states[key] == 0b00000100);
}
B32 OS_InputButton(U8 button) { return _state.button_current_states[button]; }
B32 OS_InputButtonPressed(U8 button)
{
  return (_state.button_frame_states[button] == 0b00000001);
}
B32 OS_InputButtonReleased(U8 button)
{
  return (_state.button_frame_states[button] == 0b00000010);
}
F32 OS_InputGetMouseX() { return _state.mouse_x; }
F32 OS_InputGetMouseY() { return _state.mouse_y; }
F32 OS_InputGetMouseScrollX() { return _state.mouse_scrollx; }
F32 OS_InputGetMouseScrollY() { return _state.mouse_scrolly; }
F32 OS_InputGetMouseAbsoluteScrollX() { return _state.mouse_absscrollx; }
F32 OS_InputGetMouseAbsoluteScrollY() { return _state.mouse_absscrolly; }
F32 OS_InputGetMouseDX() { return _state.mouse_x - _state.mouse_recordedx; }
F32 OS_InputGetMouseDY() { return _state.mouse_y - _state.mouse_recordedy; }
F32 OS_InputGetMouseRecordedX() { return _state.mouse_recordedx; }
F32 OS_InputGetMouseRecordedY() { return _state.mouse_recordedy; }