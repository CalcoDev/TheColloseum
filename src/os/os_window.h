#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include "base/base_string.h"
#include "base/base_types.h"

// Hacky, as I need the window define to define the types, and the types for the
// window
typedef struct OS_Window OS_Window;

typedef enum OS_WindowKeyAction
{
  WindowKeyAction_Null     = 0x0,
  WindowKeyAction_Pressed  = 0x1,
  WindowKeyAction_Released = 0x2,
} OS_WindowKeyAction;

typedef void OS_WindowResizeCallback(OS_Window* window, U32 width, U32 height);

typedef void
OS_WindowKeyCallback(OS_Window* window, U32 key, OS_WindowKeyAction action);

typedef void OS_WindowMouseButtonCallback(
    OS_Window* window, U8 btn, OS_WindowKeyAction action
);

// TODO(calco): Actually do something with the callbacks!!!!

/**
 * @brief Basic window class. For now represents a window opened via GLFW, but
 * it will eventually move on to be OS specific.
 */
typedef struct OS_Window
{
  U32 width;
  U32 height;

  String8 title;
  OS_WindowResizeCallback* resize_callback;
  OS_WindowKeyCallback* key_callback;
  OS_WindowMouseButtonCallback* mouse_button_callback;

  void* handle;
} OS_window;

void OS_WindowInit(OS_Window* window, U32 width, U32 height, String8 title);
B32 OS_WindowIsOpen(OS_Window* window);
void OS_WindowSetOpen(OS_Window* window, B32 open);
void OS_WindowPollEvents(void);
void OS_WindowFree(OS_Window* window);

void OS_WindowRegisterKeyCallback(
    OS_Window* window, OS_WindowKeyCallback callback
);
void OS_WindowRegisterButtonCallback(
    OS_Window* window, OS_WindowMouseButtonCallback callback
);
void OS_WindowRegisterResizeCallback(
    OS_Window* window, OS_WindowResizeCallback callback
);

#endif