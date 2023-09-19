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

void wrapper_glfwKeyCallback(
    GLFWwindow* glfw_window, int key, int scancode, int action, int mods
)
{
  OS_Window* os_window = (OS_Window*)glfwGetWindowUserPointer(glfw_window);

  OS_WindowKeyAction os_action = WindowKeyAction_Null;
  if (action == GLFW_PRESS)
    os_action = WindowKeyAction_Pressed;
  else if (action == GLFW_RELEASE)
    os_action = WindowKeyAction_Released;

  if (os_window->key_callback != NULL)
    os_window->key_callback(os_window, (U32)key, os_action);
}

void OS_WindowRegisterKeyCallback(
    OS_Window* window, OS_WindowKeyCallback callback
)
{
  window->key_callback = callback;
  glfwSetKeyCallback(window->handle, wrapper_glfwKeyCallback);
}

void OS_WindowRegisterButtonCallback(
    OS_Window* window, OS_WindowMouseButtonCallback callback
);
void OS_WindowRegisterResizeCallback(
    OS_Window* window, OS_WindowResizeCallback callback
);