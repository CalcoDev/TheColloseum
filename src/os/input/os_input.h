#ifndef OS_INPUT_H
#define OS_INPUT_H

#include "base/base_context.h"
#include "base/base_types.h"
#include "os_input_keycodes.h"

// TODO(calco): Actually implement OS based things. For now use GLFW.
#include "impl/os_input_keycodes_glfw.h"

// #ifdef BASE_OS_WIN
// #  include "impl/os_input_keycodes_windows.h"
// #else
// #  error Operating system input module not supported!
// #endif

void __OS_InputKeyCallback(U8 key, S32 action);
B8 __OS_InputKeyCallbackCheckRepeat(U8 key, S32 action);
void __OS_InputButtonCallback(U8 button, S32 action);
void __OS_InputCursorPosCallback(F32 xpos, F32 ypos);
void __OS_InputScrollCallback(F32 xscroll, F32 yscroll);
void __OS_InputReset();

B32 OS_InputKey(U8 key);
B32 OS_InputKeyPressed(U8 key);
B32 OS_InputKeyReleased(U8 key);
B32 OS_InputKeyHeld(U8 key);
B32 OS_InputButton(U8 button);
B32 OS_InputButtonPressed(U8 button);
B32 OS_InputButtonReleased(uU8button);
F32 OS_InputGetMouseX();
F32 OS_InputGetMouseY();
F32 OS_InputGetMouseScrollX();
F32 OS_InputGetMouseScrollY();
F32 OS_InputGetMouseAbsoluteScrollX();
F32 OS_InputGetMouseAbsoluteScrollY();
F32 OS_InputGetMouseDX();
F32 OS_InputGetMouseDY();
F32 OS_InputGetMouseRecordedX();
F32 OS_InputGetMouseRecordedY();

#endif