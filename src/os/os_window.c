#include "os_window.h"
#include "base/base_log.h"

#include <glfw/glfw3.h>

void glfwErrorCallback(int code, const char* msg)
{
  LogError("glfw error: %s (%i)", msg, code);
}

OS_Window OS_WindowInit(U32 width, U32 height, String8 title)
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

  // Center the window
  U32 window_left = video_mode->width / 2 - width / 2;
  U32 window_top  = video_mode->height / 2 - height / 2;
  glfwSetWindowPos(glfw_win, window_left, window_top);

  OS_Window os_win = {0};
  os_win.width     = width;
  os_win.height    = height;
  os_win.title     = title;
  os_win.handle    = glfw_win;
  return os_win;
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