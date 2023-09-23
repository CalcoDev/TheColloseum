#ifndef INPUT_H
#define INPUT_H

#include "base/base_bitset.h"
#include "base/base_types.h"

#include "os/os_window.h"

typedef enum I_Key
{
  Key_Space         = 0,
  Key_Apostrophe    = 1,
  Key_Comma         = 2,
  Key_Minus         = 3,
  Key_Period        = 4,
  Key_Slash         = 5,
  Key_0             = 6,
  Key_1             = 7,
  Key_2             = 8,
  Key_3             = 9,
  Key_4             = 10,
  Key_5             = 11,
  Key_6             = 12,
  Key_7             = 13,
  Key_8             = 14,
  Key_9             = 15,
  Key_Semicolon     = 16,
  Key_Equal         = 17,
  Key_A             = 18,
  Key_B             = 19,
  Key_C             = 20,
  Key_D             = 21,
  Key_E             = 22,
  Key_F             = 23,
  Key_G             = 24,
  Key_H             = 25,
  Key_I             = 26,
  Key_J             = 27,
  Key_K             = 28,
  Key_L             = 29,
  Key_M             = 30,
  Key_N             = 31,
  Key_O             = 32,
  Key_P             = 33,
  Key_Q             = 34,
  Key_R             = 35,
  Key_S             = 36,
  Key_T             = 37,
  Key_U             = 38,
  Key_V             = 39,
  Key_W             = 40,
  Key_X             = 41,
  Key_Y             = 42,
  Key_Z             = 43,
  Key_Left_Bracket  = 44,
  Key_Backslash     = 45,
  Key_Right_Bracket = 46,
  Key_Grave_Accent  = 47,
  Key_Escape        = 48,
  Key_Enter         = 49,
  Key_Tab           = 50,
  Key_Backspace     = 51,
  Key_Insert        = 52,
  Key_Delete        = 53,
  Key_Right         = 54,
  Key_Left          = 55,
  Key_Down          = 56,
  Key_Up            = 57,
  Key_Page_Up       = 58,
  Key_Page_Down     = 59,
  Key_Home          = 60,
  Key_End           = 61,
  Key_Caps_Lock     = 62,
  Key_Scroll_Lock   = 63,
  Key_Num_Lock      = 64,
  Key_Print_Screen  = 65,
  Key_Pause         = 66,
  Key_F1            = 67,
  Key_F2            = 68,
  Key_F3            = 69,
  Key_F4            = 70,
  Key_F5            = 71,
  Key_F6            = 72,
  Key_F7            = 73,
  Key_F8            = 74,
  Key_F9            = 75,
  Key_F10           = 76,
  Key_F11           = 77,
  Key_F12           = 78,
  Key_F13           = 79,
  Key_F14           = 80,
  Key_F15           = 81,
  Key_F16           = 82,
  Key_F17           = 83,
  Key_F18           = 84,
  Key_F19           = 85,
  Key_F20           = 86,
  Key_F21           = 87,
  Key_F22           = 88,
  Key_F23           = 89,
  Key_F24           = 90,
  Key_F25           = 91,
  Key_Kp_0          = 92,
  Key_Kp_1          = 93,
  Key_Kp_2          = 94,
  Key_Kp_3          = 95,
  Key_Kp_4          = 96,
  Key_Kp_5          = 97,
  Key_Kp_6          = 98,
  Key_Kp_7          = 99,
  Key_Kp_8          = 100,
  Key_Kp_9          = 101,
  Key_Kp_Decimal    = 102,
  Key_Kp_Divide     = 103,
  Key_Kp_Multiply   = 104,
  Key_Kp_Subtract   = 105,
  Key_Kp_Add        = 106,
  Key_Kp_Enter      = 107,
  Key_Kp_Equal      = 108,
  Key_Left_Shift    = 109,
  Key_Left_Control  = 110,
  Key_Left_Alt      = 111,
  Key_Left_Super    = 112,
  Key_Right_Shift   = 113,
  Key_Right_Control = 114,
  Key_Right_Alt     = 115,
  Key_Right_Super   = 116,
  Key_Menu          = 117,
  Key_MAX
} I_Key;

typedef enum I_KeyState
{
  KeyState_Up       = 0x0,
  KeyState_Pressed  = 0x1,
  KeyState_Released = 0x2,
  KeyState_Down     = 0x4
} I_KeyState;

// Can be updated in 2 ways: using custom wrappers for you input handlings
// Or calling I_InputStateUpdate(window)
typedef struct I_InputState
{
  Bitset previous_frame;
  Bitset current_frame;
} I_InputState;

I_InputState I_InputStateMake(Arena* arena);

// NOTE(calco): -- Key Helper Functions --
I_KeyState I_InputGetKeyState(I_InputState* input_state, I_Key key);

#endif