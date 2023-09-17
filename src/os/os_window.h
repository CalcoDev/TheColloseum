#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include "base/base_string.h"
#include "base/base_types.h"

// Hacky, as I need the window define to define the types, and the types for the
// window
typedef struct OS_Window OS_Window;
typedef void ResizeCallback(OS_Window* window, U32 width, U32 height);
typedef void KeyCallback(OS_Window* window, U8 key, U32 action);
typedef void ButtonCallback(OS_Window* window, U8 key, U32 action);

/**
 * @brief Basic window class. For now represents a window opened via GLFW, but
 * it will eventually move on to be OS specific.
 */
typedef struct OS_Window
{
  U32 width;
  U32 height;

  String8 title;
  ResizeCallback* resize_callback;
  KeyCallback* key_callback;
  ButtonCallback* button_callback;

  void* handle;
} OS_window;

OS_Window OS_WindowInit(U32 width, U32 height, String8 title);
B32 OS_WindowIsOpen(OS_Window* window);
void OS_WindowSetOpen(OS_Window* window, B32 open);
void OS_WindowPollEvents(void);
void OS_WindowFree(OS_Window* window);

#endif