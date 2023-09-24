#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include "base/base_bitset.h"
#include "base/base_string.h"
#include "base/base_types.h"

typedef enum OS_Key
{
  Key_Space        = 0,
  Key_Apostrophe   = 1,
  Key_Comma        = 2,
  Key_Minus        = 3,
  Key_Period       = 4,
  Key_Slash        = 5,
  Key_0            = 6,
  Key_1            = 7,
  Key_2            = 8,
  Key_3            = 9,
  Key_4            = 10,
  Key_5            = 11,
  Key_6            = 12,
  Key_7            = 13,
  Key_8            = 14,
  Key_9            = 15,
  Key_Semicolon    = 16,
  Key_Equal        = 17,
  Key_A            = 18,
  Key_B            = 19,
  Key_C            = 20,
  Key_D            = 21,
  Key_E            = 22,
  Key_F            = 23,
  Key_G            = 24,
  Key_H            = 25,
  Key_I            = 26,
  Key_J            = 27,
  Key_K            = 28,
  Key_L            = 29,
  Key_M            = 30,
  Key_N            = 31,
  Key_O            = 32,
  Key_P            = 33,
  Key_Q            = 34,
  Key_R            = 35,
  Key_S            = 36,
  Key_T            = 37,
  Key_U            = 38,
  Key_V            = 39,
  Key_W            = 40,
  Key_X            = 41,
  Key_Y            = 42,
  Key_Z            = 43,
  Key_LeftBracket  = 44,
  Key_Backslash    = 45,
  Key_RightBracket = 46,
  Key_Grave_Accent = 47,
  Key_Escape       = 48,
  Key_Enter        = 49,
  Key_Tab          = 50,
  Key_Backspace    = 51,
  Key_Insert       = 52,
  Key_Delete       = 53,
  Key_Right        = 54,
  Key_Left         = 55,
  Key_Down         = 56,
  Key_Up           = 57,
  Key_PageUp       = 58,
  Key_PageDown     = 59,
  Key_Home         = 60,
  Key_End          = 61,
  Key_CapsLock     = 62,
  Key_ScrollLock   = 63,
  Key_NumLock      = 64,
  Key_PrintScreen  = 65,
  Key_Pause        = 66,
  Key_F1           = 67,
  Key_F2           = 68,
  Key_F3           = 69,
  Key_F4           = 70,
  Key_F5           = 71,
  Key_F6           = 72,
  Key_F7           = 73,
  Key_F8           = 74,
  Key_F9           = 75,
  Key_F10          = 76,
  Key_F11          = 77,
  Key_F12          = 78,
  Key_F13          = 79,
  Key_F14          = 80,
  Key_F15          = 81,
  Key_F16          = 82,
  Key_F17          = 83,
  Key_F18          = 84,
  Key_F19          = 85,
  Key_F20          = 86,
  Key_F21          = 87,
  Key_F22          = 88,
  Key_F23          = 89,
  Key_F24          = 90,
  Key_F25          = 91,
  Key_Kp0          = 92,
  Key_Kp1          = 93,
  Key_Kp2          = 94,
  Key_Kp3          = 95,
  Key_Kp4          = 96,
  Key_Kp5          = 97,
  Key_Kp6          = 98,
  Key_Kp7          = 99,
  Key_Kp8          = 100,
  Key_Kp9          = 101,
  Key_KpDecimal    = 102,
  Key_KpDivide     = 103,
  Key_KpMultiply   = 104,
  Key_KpSubtract   = 105,
  Key_KpAdd        = 106,
  Key_KpEnter      = 107,
  Key_KpEqual      = 108,
  Key_LeftShift    = 109,
  Key_LeftControl  = 110,
  Key_LeftAlt      = 111,
  Key_LeftSuper    = 112,
  Key_RightShift   = 113,
  Key_RightControl = 114,
  Key_RightAlt     = 115,
  Key_RightSuper   = 116,
  Key_Menu         = 117,
  Key_Mouse1       = 118,
  Key_Mouse2       = 119,
  Key_Mouse3       = 120,
  Key_Mouse4       = 121,
  Key_Mouse5       = 122,
  Key_Mouse6       = 123,
  Key_Mouse7       = 124,
  Key_Mouse8       = 125,
  Key_Joystick1    = 126,
  Key_Joystick2    = 127,
  Key_Joystick3    = 128,
  Key_Joystick4    = 129,
  Key_Joystick5    = 130,
  Key_Joystick6    = 131,
  Key_Joystick7    = 132,
  Key_Joystick8    = 133,
  Key_Joystick9    = 134,
  Key_Joystick10   = 135,
  Key_Joystick11   = 136,
  Key_Joystick12   = 137,
  Key_Joystick13   = 138,
  Key_Joystick14   = 139,
  Key_Joystick15   = 140,
  Key_Joystick16   = 141,
  Key_MAX
} OS_Key;

typedef struct OS_Window OS_Window;

typedef enum OS_WindowKeyAction
{
  WindowKeyAction_Null = 0x0,
  WindowKeyAction_Down = 0x1,
  WindowKeyAction_Up   = 0x2,
} OS_WindowKeyAction;

typedef enum OS_WindowMouseVisibility
{
  WindowMouseVisibility_Shown    = 0x1,
  WindowMouseVisibility_Hidden   = 0x2,
  WindowMouseVisibility_Disabled = 0x3,
} OS_WindowMouseVisibility;

typedef void OS_WindowResizeCallback(OS_Window* window, U32 width, U32 height);

typedef void
OS_WindowKeyCallback(OS_Window* window, U32 key, OS_WindowKeyAction action);

typedef void OS_WindowMouseButtonCallback(
    OS_Window* window, U8 btn, OS_WindowKeyAction action
);

typedef void
OS_WindowMousePositionCallback(OS_Window* window, F32 pos_x, F32 pos_y);

#define OS_WINDOW_MAX_RESIZE_CALLBACK_SIZE         1
#define OS_WINDOW_MAX_KEY_CALLBACK_SIZE            1
#define OS_WINDOW_MAX_MOUSE_BUTTON_CALLBACK_SIZE   1
#define OS_WINDOW_MAX_MOUSE_POSITION_CALLBACK_SIZE 1

/**
 * @brief Basic window class. For now represents a window opened via GLFW, but
 * it will eventually move on to be OS specific.
 * @warning Uses the OS_WINDOW_MAX_CALLBACK_SIZE preprocessor macro to create an
 * array of however many callbacks.
 */
typedef struct OS_Window
{
  U32 width;
  U32 height;

  String8 title;
  OS_WindowResizeCallback* resize_callbacks[OS_WINDOW_MAX_RESIZE_CALLBACK_SIZE];
  OS_WindowKeyCallback* key_callbacks[OS_WINDOW_MAX_KEY_CALLBACK_SIZE];
  OS_WindowMouseButtonCallback*
      mouse_button_callbacks[OS_WINDOW_MAX_MOUSE_BUTTON_CALLBACK_SIZE];
  OS_WindowMousePositionCallback*
      mouse_position_callbacks[OS_WINDOW_MAX_MOUSE_POSITION_CALLBACK_SIZE];

  Bitset input;

  void* handle;
} OS_window;

void OS_WindowInit(
    Arena* arena, OS_Window* window, U32 width, U32 height, String8 title
);
B32 OS_WindowIsOpen(OS_Window* window);
void OS_WindowSetOpen(OS_Window* window, B32 open);
void OS_WindowPollEvents(void);
void OS_WindowFree(OS_Window* window);

void OS_WindowSetMouseVisibility(
    OS_Window* window, OS_WindowMouseVisibility visibility
);

// NOTE(calco): -- Window Callback Functions --
void OS_WindowRegisterResizeCallback(
    OS_Window* window, OS_WindowResizeCallback callback
);
void OS_WindowRegisterKeyCallback(
    OS_Window* window, OS_WindowKeyCallback callback
);
void OS_WindowRegisterMouseButtonCallback(
    OS_Window* window, OS_WindowMouseButtonCallback callback
);
void OS_WindowRegisterMousePositionCallback(
    OS_Window* window, OS_WindowMousePositionCallback callback
);

#endif