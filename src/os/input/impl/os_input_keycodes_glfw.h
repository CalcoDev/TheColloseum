#ifndef OS_Input_CODES_GLFW_H
#define OS_Input_CODES_GLFW_H

#include "Windows.h"

#include "base/base_types.h"

// NOTE(calco): -- Actions --
#define GLFWInput_RELEASE 0
#define GLFWInput_PRESS   1
#define GLFWInput_REPEAT  2

// NOTE(calco): -- Mouse Buttons --
#define GLFWInput_MOUSE_BUTTON_1      0
#define GLFWInput_MOUSE_BUTTON_2      1
#define GLFWInput_MOUSE_BUTTON_3      2
#define GLFWInput_MOUSE_BUTTON_LEFT   GLFWInput_MOUSE_BUTTON_1
#define GLFWInput_MOUSE_BUTTON_RIGHT  GLFWInput_MOUSE_BUTTON_2
#define GLFWInput_MOUSE_BUTTON_MIDDLE GLFWInput_MOUSE_BUTTON_3

// NOTE(calco): -- Numeric Keys --
#define GLFWInput_KEY_0 48
#define GLFWInput_KEY_1 49
#define GLFWInput_KEY_2 50
#define GLFWInput_KEY_3 51
#define GLFWInput_KEY_4 52
#define GLFWInput_KEY_5 53
#define GLFWInput_KEY_6 54
#define GLFWInput_KEY_7 55
#define GLFWInput_KEY_8 56
#define GLFWInput_KEY_9 57

// NOTE(calco): -- Alphabetical Keys --
#define GLFWInput_KEY_A 65
#define GLFWInput_KEY_B 66
#define GLFWInput_KEY_C 67
#define GLFWInput_KEY_D 68
#define GLFWInput_KEY_E 69
#define GLFWInput_KEY_F 70
#define GLFWInput_KEY_G 71
#define GLFWInput_KEY_H 72
#define GLFWInput_KEY_I 73
#define GLFWInput_KEY_J 74
#define GLFWInput_KEY_K 75
#define GLFWInput_KEY_L 76
#define GLFWInput_KEY_M 77
#define GLFWInput_KEY_N 78
#define GLFWInput_KEY_O 79
#define GLFWInput_KEY_P 80
#define GLFWInput_KEY_Q 81
#define GLFWInput_KEY_R 82
#define GLFWInput_KEY_S 83
#define GLFWInput_KEY_T 84
#define GLFWInput_KEY_U 85
#define GLFWInput_KEY_V 86
#define GLFWInput_KEY_W 87
#define GLFWInput_KEY_X 88
#define GLFWInput_KEY_Y 89
#define GLFWInput_KEY_Z 90

// NOTE(calco): -- Arrow Keys --
#define GLFWInput_KEY_RIGHT 262
#define GLFWInput_KEY_LEFT  263
#define GLFWInput_KEY_DOWN  264
#define GLFWInput_KEY_UP    265

// NOTE(calco): -- Numpad --
#define GLFWInput_KEY_KP_0        320
#define GLFWInput_KEY_KP_1        321
#define GLFWInput_KEY_KP_2        322
#define GLFWInput_KEY_KP_3        323
#define GLFWInput_KEY_KP_4        324
#define GLFWInput_KEY_KP_5        325
#define GLFWInput_KEY_KP_6        326
#define GLFWInput_KEY_KP_7        327
#define GLFWInput_KEY_KP_8        328
#define GLFWInput_KEY_KP_9        329
#define GLFWInput_KEY_KP_DECIMAL  330
#define GLFWInput_KEY_KP_DIVIDE   331
#define GLFWInput_KEY_KP_MULTIPLY 332
#define GLFWInput_KEY_KP_SUBTRACT 333
#define GLFWInput_KEY_KP_ADD      334
#define GLFWInput_KEY_KP_ENTER    335
#define GLFWInput_KEY_KP_EQUAL    336

// NOTE(calco): -- Action Keys --
#define GLFWInput_KEY_SPACE         32
#define GLFWInput_KEY_APOSTROPHE    39 /* ' */
#define GLFWInput_KEY_COMMA         44 /* , */
#define GLFWInput_KEY_MINUS         45 /* - */
#define GLFWInput_KEY_PERIOD        46 /* . */
#define GLFWInput_KEY_SLASH         47 /* / */
#define GLFWInput_KEY_SEMICOLON     59 /* ; */
#define GLFWInput_KEY_EQUAL         61 /* = */
#define GLFWInput_KEY_LEFT_BRACKET  91 /* [ */
#define GLFWInput_KEY_BACKSLASH     92 /* \ */
#define GLFWInput_KEY_RIGHT_BRACKET 93 /* ] */
#define GLFWInput_KEY_GRAVE_ACCENT  96 /* ` */

#define GLFWInput_KEY_ESCAPE    256
#define GLFWInput_KEY_ENTER     257
#define GLFWInput_KEY_TAB       258
#define GLFWInput_KEY_BACKSPACE 259
#define GLFWInput_KEY_INSERT    260
#define GLFWInput_KEY_DELETE    261

#define GLFWInput_KEY_LEFT_SHIFT    340
#define GLFWInput_KEY_LEFT_CONTROL  341
#define GLFWInput_KEY_LEFT_ALT      342
#define GLFWInput_KEY_LEFT_SUPER    343
#define GLFWInput_KEY_RIGHT_SHIFT   344
#define GLFWInput_KEY_RIGHT_CONTROL 345
#define GLFWInput_KEY_RIGHT_ALT     346
#define GLFWInput_KEY_RIGHT_SUPER   347
#define GLFWInput_KEY_MENU          348

#define GLFWInput_KEY_PAGE_UP      266
#define GLFWInput_KEY_PAGE_DOWN    267
#define GLFWInput_KEY_HOME         268
#define GLFWInput_KEY_END          269
#define GLFWInput_KEY_CAPS_LOCK    280
#define GLFWInput_KEY_SCROLL_LOCK  281
#define GLFWInput_KEY_NUM_LOCK     282
#define GLFWInput_KEY_PRINT_SCREEN 283
#define GLFWInput_KEY_PAUSE        284

// NOTE(calco): -- Function Keys --
#define GLFWInput_KEY_F1  290
#define GLFWInput_KEY_F2  291
#define GLFWInput_KEY_F3  292
#define GLFWInput_KEY_F4  293
#define GLFWInput_KEY_F5  294
#define GLFWInput_KEY_F6  295
#define GLFWInput_KEY_F7  296
#define GLFWInput_KEY_F8  297
#define GLFWInput_KEY_F9  298
#define GLFWInput_KEY_F10 299
#define GLFWInput_KEY_F11 300
#define GLFWInput_KEY_F12 301

static inline U8 __OS_InputTranslateGLFW_Actions(U32 input)
{
  switch (input)
  {
      // Actions
    case GLFWInput_RELEASE:
      return 2;
    case GLFWInput_PRESS:
      return 1;
    case GLFWInput_REPEAT:
      return 3;
  }
}

static inline U8 __OS_InputTranslateGLFW_Mouse(U32 input)
{
  switch (input)
  {
      // Mouse Buttons
    case GLFWInput_MOUSE_BUTTON_1:
      return VK_LBUTTON;
    case GLFWInput_MOUSE_BUTTON_2:
      return VK_RBUTTON;
    case GLFWInput_MOUSE_BUTTON_3:
      return VK_MBUTTON;
  }
}

static inline U8 __OS_InputTranslateGLFW_Key(U32 input)
{
  switch (input)
  {
    // Numeric Keys
    case GLFWInput_KEY_0:
      return '0';
    case GLFWInput_KEY_1:
      return '1';
    case GLFWInput_KEY_2:
      return '2';
    case GLFWInput_KEY_3:
      return '3';
    case GLFWInput_KEY_4:
      return '4';
    case GLFWInput_KEY_5:
      return '5';
    case GLFWInput_KEY_6:
      return '6';
    case GLFWInput_KEY_7:
      return '7';
    case GLFWInput_KEY_8:
      return '8';
    case GLFWInput_KEY_9:
      return '9';

    // Alphabetical Keys
    case GLFWInput_KEY_A:
      return 'A';
    case GLFWInput_KEY_B:
      return 'B';
    case GLFWInput_KEY_C:
      return 'C';
    case GLFWInput_KEY_D:
      return 'D';
    case GLFWInput_KEY_E:
      return 'E';
    case GLFWInput_KEY_F:
      return 'F';
    case GLFWInput_KEY_G:
      return 'G';
    case GLFWInput_KEY_H:
      return 'H';
    case GLFWInput_KEY_I:
      return 'I';
    case GLFWInput_KEY_J:
      return 'J';
    case GLFWInput_KEY_K:
      return 'K';
    case GLFWInput_KEY_L:
      return 'L';
    case GLFWInput_KEY_M:
      return 'M';
    case GLFWInput_KEY_N:
      return 'N';
    case GLFWInput_KEY_O:
      return 'O';
    case GLFWInput_KEY_P:
      return 'P';
    case GLFWInput_KEY_Q:
      return 'Q';
    case GLFWInput_KEY_R:
      return 'R';
    case GLFWInput_KEY_S:
      return 'S';
    case GLFWInput_KEY_T:
      return 'T';
    case GLFWInput_KEY_U:
      return 'U';
    case GLFWInput_KEY_V:
      return 'V';
    case GLFWInput_KEY_W:
      return 'W';
    case GLFWInput_KEY_X:
      return 'X';
    case GLFWInput_KEY_Y:
      return 'Y';
    case GLFWInput_KEY_Z:
      return 'Z';

    // Arrow Keys
    case GLFWInput_KEY_RIGHT:
      return VK_RIGHT;
    case GLFWInput_KEY_LEFT:
      return VK_LEFT;
    case GLFWInput_KEY_DOWN:
      return VK_DOWN;
    case GLFWInput_KEY_UP:
      return VK_UP;

    // Numpad Keys
    case GLFWInput_KEY_KP_0:
      return VK_NUMPAD0;
    case GLFWInput_KEY_KP_1:
      return VK_NUMPAD1;
    case GLFWInput_KEY_KP_2:
      return VK_NUMPAD2;
    case GLFWInput_KEY_KP_3:
      return VK_NUMPAD3;
    case GLFWInput_KEY_KP_4:
      return VK_NUMPAD4;
    case GLFWInput_KEY_KP_5:
      return VK_NUMPAD5;
    case GLFWInput_KEY_KP_6:
      return VK_NUMPAD6;
    case GLFWInput_KEY_KP_7:
      return VK_NUMPAD7;
    case GLFWInput_KEY_KP_8:
      return VK_NUMPAD8;
    case GLFWInput_KEY_KP_9:
      return VK_NUMPAD9;
    case GLFWInput_KEY_KP_DECIMAL:
      return VK_DECIMAL;
    case GLFWInput_KEY_KP_DIVIDE:
      return VK_DIVIDE;
    case GLFWInput_KEY_KP_MULTIPLY:
      return VK_MULTIPLY;
    case GLFWInput_KEY_KP_SUBTRACT:
      return VK_SUBTRACT;
    case GLFWInput_KEY_KP_ADD:
      return VK_ADD;
    case GLFWInput_KEY_KP_ENTER:
      return VK_RETURN; // VK_RETURN is used for the Enter key on the numpad.
    case GLFWInput_KEY_KP_EQUAL:
      return VK_OEM_NEC_EQUAL; // VK_OEM_NEC_EQUAL is used for the "equal" key
                               // on some numpads.

    // Action Keys
    case GLFWInput_KEY_SPACE:
      return VK_SPACE;
    case GLFWInput_KEY_APOSTROPHE:
      return VK_OEM_7; // ' key
    case GLFWInput_KEY_COMMA:
      return VK_OEM_COMMA; // , key
    case GLFWInput_KEY_MINUS:
      return VK_OEM_MINUS; // - key
    case GLFWInput_KEY_PERIOD:
      return VK_OEM_PERIOD; // . key
    case GLFWInput_KEY_SLASH:
      return VK_OEM_2; // / key
    case GLFWInput_KEY_SEMICOLON:
      return VK_OEM_1; // ; key
    case GLFWInput_KEY_EQUAL:
      return VK_OEM_PLUS; // = key
    case GLFWInput_KEY_LEFT_BRACKET:
      return VK_OEM_4; // [ key
    case GLFWInput_KEY_BACKSLASH:
      return VK_OEM_5; // \ key
    case GLFWInput_KEY_RIGHT_BRACKET:
      return VK_OEM_6; // ] key
    case GLFWInput_KEY_GRAVE_ACCENT:
      return VK_OEM_3; // ` key

    // Special Keys
    case GLFWInput_KEY_ESCAPE:
      return VK_ESCAPE;
    case GLFWInput_KEY_ENTER:
      return VK_RETURN;
    case GLFWInput_KEY_TAB:
      return VK_TAB;
    case GLFWInput_KEY_BACKSPACE:
      return VK_BACK;
    case GLFWInput_KEY_INSERT:
      return VK_INSERT;
    case GLFWInput_KEY_DELETE:
      return VK_DELETE;

    case GLFWInput_KEY_LEFT_SHIFT:
      return VK_LSHIFT;
    case GLFWInput_KEY_LEFT_CONTROL:
      return VK_LCONTROL;
    case GLFWInput_KEY_LEFT_ALT:
      return VK_LMENU;
    case GLFWInput_KEY_LEFT_SUPER:
      return VK_LWIN;
    case GLFWInput_KEY_RIGHT_SHIFT:
      return VK_RSHIFT;
    case GLFWInput_KEY_RIGHT_CONTROL:
      return VK_RCONTROL;
    case GLFWInput_KEY_RIGHT_ALT:
      return VK_RMENU;
    case GLFWInput_KEY_RIGHT_SUPER:
      return VK_RWIN;
    case GLFWInput_KEY_MENU:
      return VK_APPS;

    // Additional Keys
    case GLFWInput_KEY_PAGE_UP:
      return VK_PRIOR;
    case GLFWInput_KEY_PAGE_DOWN:
      return VK_NEXT;
    case GLFWInput_KEY_HOME:
      return VK_HOME;
    case GLFWInput_KEY_END:
      return VK_END;
    case GLFWInput_KEY_CAPS_LOCK:
      return VK_CAPITAL;
    case GLFWInput_KEY_SCROLL_LOCK:
      return VK_SCROLL;
    case GLFWInput_KEY_NUM_LOCK:
      return VK_NUMLOCK;
    case GLFWInput_KEY_PRINT_SCREEN:
      return VK_PRINT;
    case GLFWInput_KEY_PAUSE:
      return VK_PAUSE;

      // Function Keys
    case GLFWInput_KEY_F1:
      return VK_F1;
    case GLFWInput_KEY_F2:
      return VK_F2;
    case GLFWInput_KEY_F3:
      return VK_F3;
    case GLFWInput_KEY_F4:
      return VK_F4;
    case GLFWInput_KEY_F5:
      return VK_F5;
    case GLFWInput_KEY_F6:
      return VK_F6;
    case GLFWInput_KEY_F7:
      return VK_F7;
    case GLFWInput_KEY_F8:
      return VK_F8;
    case GLFWInput_KEY_F9:
      return VK_F9;
    case GLFWInput_KEY_F10:
      return VK_F10;
    case GLFWInput_KEY_F11:
      return VK_F11;
    case GLFWInput_KEY_F12:
      return VK_F12;
  }
}

#endif