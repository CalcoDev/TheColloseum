#include <glfw/glfw3.h>
#include <stdio.h>

#include "base/base_include.h"
#include "os/os.h"

void glfwErrorCallback(int code, const char* msg)
{
  LogError("glfw error: %s (%i)", msg, code);
}

void ProcessWindowInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main()
{
  // NOTES(calco): Init Memory
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Megabytes(1));

  // NOTES(calco): GLFW
  Log("Initialising glfw.", "");
  if (!glfwInit())
  {
    LogFatal("Error initializing GLFW!", "");
  }

  glfwSetErrorCallback(glfwErrorCallback);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  GLFWvidmode* video_mode = glfwGetVideoMode(monitor);
  U32 window_width = video_mode->width / 2;
  U32 window_height = video_mode->height / 2;

  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE); // No scale - high dpi
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Do not create opengl context

  Log("Creating glfw window.", "");
  GLFWwindow* window =
      glfwCreateWindow(window_width, window_height, "Direct X-ing", NULL, NULL);
  if (window == NULL)
  {
    glfwTerminate();
    LogFatal("Error occured creating glfw window.", "");
  }

  // Center the window
  U32 window_left = video_mode->width / 2 - window_width / 2;
  U32 window_top = video_mode->height / 2 - window_height / 2;
  glfwSetWindowPos(window, window_left, window_top);

  // Set up key callbacks.
  glfwSetKeyCallback(window, ProcessWindowInput);

  Log("Starting game loop.", "");
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    // Render
    // Update
  }

  Log("Destroying window.", "");
  glfwDestroyWindow(window);
  Log("Terminating glfw.", "");
  glfwTerminate();
  ArenaRelease(&arena);
  return 0;
}