#include <glad/glad.h>
// seaprate so that glad is always first
#include <glfw/glfw3.h>
#include <stdio.h>

#include "base/base_include.h"
#include "os/os.h"
#include "render/render.h"

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

  // Init opengl in window.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Mac

  GLFWmonitor* monitor    = glfwGetPrimaryMonitor();
  GLFWvidmode* video_mode = glfwGetVideoMode(monitor);
  U32 window_width        = video_mode->width / 2;
  U32 window_height       = video_mode->height / 2;

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
  U32 window_top  = video_mode->height / 2 - window_height / 2;
  glfwSetWindowPos(window, window_left, window_top);

  // Set up key callbacks.
  glfwSetKeyCallback(window, ProcessWindowInput);

  // Set window to current context
  glfwMakeContextCurrent(window);

  // Init glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    LogFatal("Error initialising glad.", "");
    glfwTerminate();
    return -1;
  }

  // Data
  F32 vertices[] = {
      0.5f,  0.5f,  // top right
      0.5f,  -0.5f, // bottom right
      -0.5f, -0.5f, // bottom left
      -0.5f, 0.5f,  // top left
  };
  U32 indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  // Create a vertex buffer
  R_Buffer vertex_buffer = {0};
  R_BufferInit(&vertex_buffer, BufferFlag_Type_Vertex);
  R_BufferData(&vertex_buffer, vertices, sizeof(vertices) / sizeof(F32));

  // Create an index buffer

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