#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// windows only something
#include <windows.h>

#include "base/base_types.h"

char* getShaderContent(const char* fileName)
{
  FILE* fp;
  long size = 0;
  char* shaderContent;

  fp = fopen(fileName, "rb");
  if (fp == NULL)
  {
    return "";
  }
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp) + 1;
  fclose(fp);

  fp = fopen(fileName, "r");
  shaderContent = memset(malloc(size), '\0', size);
  fread(shaderContent, 1, size - 1, fp);
  fclose(fp);

  return shaderContent;
}

void glfwErrorCallback(int code, const char* msg)
{
  printf("GLFW error: %d - %s\\n", code, msg);
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main()
{
  glfwInit();

  glfwSetErrorCallback(glfwErrorCallback);

  // Give glfw hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Mac

  // Create and init a window
  GLFWwindow* window = glfwCreateWindow(800, 800, "sup ohpengul", NULL, NULL);
  if (window == NULL)
  {
    printf("Failed to create GLFW window.\\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // Init glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD.\\n");
    glfwTerminate();
    return -1;
  }

  // Set up the viewport and window
  // Map [-1, -1] to [width, height]
  glViewport(0, 0, 800, 800);

  // TODO(calco): NOT ASSETS IN PROD, BUT IN SRC.
  char* vs_path =
      _fullpath(NULL, "..\\assets\\shaders\\default_vert.vs", _MAX_PATH);
  char* fs_path =
      _fullpath(NULL, "..\\assets\\shaders\\default_frag.fs", _MAX_PATH);

  // Load vertex and fragment shaders
  char* vs_source = getShaderContent(vs_path);
  char* fs_source = getShaderContent(fs_path);

  printf("Vertex shader source:\n%s\n", vs_source);
  printf("Fragment shader source:\n%s\n", fs_source);

  // Set up the individual shaders
  U32 vs_handle = glCreateShader(GL_VERTEX_SHADER);
  U32 fs_handle = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vs_handle, 1, &vs_source, NULL);
  glShaderSource(fs_handle, 1, &fs_source, NULL);

  glCompileShader(vs_handle);
  glCompileShader(fs_handle);

  S32 status;
  char error_buffer[512];
  glGetShaderiv(vs_handle, GL_COMPILE_STATUS, &status);
  printf("Vertex shader compilation status: %i\n", status);
  if (!status)
  {
    glGetShaderInfoLog(vs_handle, 512, NULL, error_buffer);
    printf("%s\n", error_buffer);
  }

  glGetShaderiv(fs_handle, GL_COMPILE_STATUS, &status);
  printf("Fragment shader compilation status: %i\n", status);
  if (!status)
  {
    glGetShaderInfoLog(fs_handle, 512, NULL, error_buffer);
    printf("%s\n", error_buffer);
  }

  // Set up the shader program
  U32 program_handle = glCreateProgram();
  glAttachShader(program_handle, vs_handle);
  glAttachShader(program_handle, fs_handle);

  glLinkProgram(program_handle);

  glGetProgramiv(program_handle, GL_LINK_STATUS, &status);
  printf("Program linking status: %i\n", status);
  if (!status)
  {
    glGetProgramInfoLog(program_handle, 512, NULL, error_buffer);
    printf("%s\n", error_buffer);
  }

  // glUseProgram(program_handle);

  // Vertices and actual data
  F32 vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f,  0.0f,
                    0.5f,  -0.5f, 0.5f, 0.5f,  -0.5f, 0.5f};

  // Set vertex array object and vertex buffer object
  U32 vertex_array_handle;
  glGenVertexArrays(1, &vertex_array_handle);

  U32 vertex_buffer_handle;
  glGenBuffers(1, &vertex_buffer_handle);

  // 1. bind vao
  glBindVertexArray(vertex_array_handle);

  // 2. Copy data to vertex_buffer_handle
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_handle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 3. Tell OpenGL what data we're sending. Should be called every time we want
  // to draw something. This is why we want to use a Vertex Array Object
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(F32), (void*)0);
  glEnableVertexAttribArray(0);

  // NOTES: CALCO
  // 4. Draw:
  // glUseProgram(shader)
  // glBindVertexArray(vao)
  // drwa()

  // render loop
  while (!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // triangles
    glUseProgram(program_handle);
    glBindVertexArray(vertex_array_handle);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(F32));

    // events and buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(program_handle);
  glDeleteShader(vs_handle);
  glDeleteShader(fs_handle);

  glfwTerminate();
  return 0;
}