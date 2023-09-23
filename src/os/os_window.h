#ifndef OS_WINDOW_H
#define OS_WINDOW_H

#include "base/base_string.h"
#include "base/base_types.h"

// Hacky, as I need the window define to define the types, and the types for the
// window
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

// TODO(calco): Actually do something with the callbacks!!!!

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

  void* handle;
} OS_window;

void OS_WindowInit(OS_Window* window, U32 width, U32 height, String8 title);
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