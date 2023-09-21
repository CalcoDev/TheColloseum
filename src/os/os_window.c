#include "os_window.h"
#include "base/base_log.h"

#include <glfw/glfw3.h>

// TODO(calco): Allow custom error callback.
void glfwErrorCallback(int code, const char* msg)
{
  LogError("glfw error: %s (%i)", msg, code);
}

void OS_WindowInit(OS_Window* window, U32 width, U32 height, String8 title)
{
  Log("Initialising GLFW window.", "");

  if (!glfwInit())
    LogFatal("Error initializing GLFW!", "");

  glfwSetErrorCallback(glfwErrorCallback);

  GLFWmonitor* monitor    = glfwGetPrimaryMonitor();
  GLFWvidmode* video_mode = glfwGetVideoMode(monitor);

  GLFWwindow* glfw_win =
      glfwCreateWindow(width, height, title.data, NULL, NULL);
  if (glfw_win == NULL)
  {
    glfwTerminate();
    LogFatal("Error occured while creating GLFW window.", "");
  }

  // Way of getting OS_Window from glfw window.
  // A bit scuffed for multi threaded things I assume tho
  glfwSetWindowUserPointer(glfw_win, window);

  // Center the window
  U32 window_left = video_mode->width / 2 - width / 2;
  U32 window_top  = video_mode->height / 2 - height / 2;
  glfwSetWindowPos(glfw_win, window_left, window_top);

  window->width  = width;
  window->height = height;
  window->title  = title;
  window->handle = glfw_win;
}

B32 OS_WindowIsOpen(OS_Window* window)
{
  return !glfwWindowShouldClose(window->handle);
}

void OS_WindowSetOpen(OS_Window* window, B32 open)
{
  glfwSetWindowShouldClose(window->handle, !open);
}

void OS_WindowPollEvents(void) { glfwPollEvents(); }

void OS_WindowFree(OS_Window* window)
{
  Log("Destroying GLFW window and terminating context.", "");

  glfwDestroyWindow(window->handle);
  glfwTerminate();
}

void OS_WindowSetMouseVisibility(
    OS_Window* window, OS_WindowMouseVisibility visibility
)
{
  if (visibility == WindowMouseVisibility_Shown)
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  else if (visibility == WindowMouseVisibility_Hidden)
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  else if (visibility == WindowMouseVisibility_Disabled)
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// NOTE(calco): -- GLFW Callback Wrappers --
void wrapper_glfwResizeCallback(GLFWwindow* glfw_window, int width, int height)
{
  OS_Window* os_window = (OS_Window*)glfwGetWindowUserPointer(glfw_window);

  if (os_window->resize_callback != NULL)
    os_window->resize_callback(os_window, width, height);
}

void wrapper_glfwKeyCallback(
    GLFWwindow* glfw_window, int key, int scancode, int action, int mods
)
{
  OS_Window* os_window = (OS_Window*)glfwGetWindowUserPointer(glfw_window);

  OS_WindowKeyAction os_action = WindowKeyAction_Null;
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
    os_action = WindowKeyAction_Down;
  else if (action == GLFW_RELEASE)
    os_action = WindowKeyAction_Up;

  if (os_window->key_callback != NULL)
    os_window->key_callback(os_window, (U32)key, os_action);
}

void wrapper_glfwMouseButtonCallback(
    GLFWwindow* glfw_window, int button, int action, int mods
)
{
  OS_Window* os_window = (OS_Window*)glfwGetWindowUserPointer(glfw_window);

  OS_WindowKeyAction os_action = WindowKeyAction_Null;
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
    os_action = WindowKeyAction_Down;
  else if (action == GLFW_RELEASE)
    os_action = WindowKeyAction_Up;

  if (os_window->mouse_button_callback != NULL)
    os_window->mouse_button_callback(os_window, (U8)button, os_action);
}

void wrapper_glfwMousePositionCallback(
    GLFWwindow* glfw_window, double pos_x, double pos_y
)
{
  OS_Window* os_window = (OS_Window*)glfwGetWindowUserPointer(glfw_window);

  if (os_window->mouse_position_callback != NULL)
    os_window->mouse_position_callback(os_window, (F32)pos_x, (F32)pos_y);
}

// NOTE(calco): -- Window Callback Functions --
void OS_WindowRegisterResizeCallback(
    OS_Window* window, OS_WindowResizeCallback callback
)
{
  window->resize_callback = callback;
  glfwSetWindowSizeCallback(window->handle, wrapper_glfwResizeCallback);
}

void OS_WindowRegisterKeyCallback(
    OS_Window* window, OS_WindowKeyCallback callback
)
{
  window->key_callback = callback;
  glfwSetKeyCallback(window->handle, wrapper_glfwKeyCallback);
}

void OS_WindowRegisterMouseButtonCallback(
    OS_Window* window, OS_WindowMouseButtonCallback callback
)
{
  window->mouse_button_callback = callback;
  glfwSetMouseButtonCallback(window->handle, wrapper_glfwMouseButtonCallback);
}

void OS_WindowRegisterMousePositionCallback(
    OS_Window* window, OS_WindowMousePositionCallback callback
)
{
  window->mouse_position_callback = callback;
  glfwSetCursorPosCallback(window->handle, wrapper_glfwMousePositionCallback);
}