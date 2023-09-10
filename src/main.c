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
  OS_Init();

  PrecisionTime prec_time = OS_TimeMicroseconds();

  // DenseTime dense_time = OS_TimeUniversal();
  DateTime universal_date   = OS_TimeUniversal();
  DenseTime universal_dense = DenseTimeFromDateTime(universal_date);
  DateTime decoded          = DateTimeFromDenseTime(universal_dense);

  DateTime local_date          = OS_TimeLocal();
  DateTime conv_local_date     = OS_TimeLocalFromUniversal(universal_date);
  DateTime conv_universal_date = OS_TimeUniversalFromLocal(local_date);

  PrecisionTime prec_time2 = OS_TimeMicroseconds();

  return 0;
}

int _main()
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
      0, 3, 1, // first triangle
      1, 3, 2  // second triangle
  };

  // Create a vertex buffer
  R_Buffer vertex_buffer = {0};
  R_BufferInit(&vertex_buffer, BufferFlag_Type_Vertex);
  R_BufferData(&vertex_buffer, vertices, sizeof(vertices));

  // Create an index buffer
  R_Buffer index_buffer = {0};
  R_BufferInit(&index_buffer, BufferFlag_Type_Index);
  R_BufferData(&index_buffer, indices, sizeof(indices));

  // Do some shaders real quick.
  String8 exe_path = OS_PathExecutableDir(&arena);

  String8 vs_path = OS_PathRelative(
      &arena, exe_path, Str8Lit("./assets/shaders/default_vert.vs")
  );
  String8 vs_data = OS_FileRead(&arena, vs_path);
  R_Shader vs;
  R_ShaderInit(&vs, ShaderType_Vertex);
  R_ShaderData(&vs, vs_data);

  String8 fs_path = OS_PathRelative(
      &arena, exe_path, Str8Lit("./assets/shaders/default_frag.fs")
  );
  String8 fs_data = OS_FileRead(&arena, fs_path);
  R_Shader fs;
  R_ShaderInit(&fs, ShaderType_Fragment);
  R_ShaderData(&fs, fs_data);

  R_Shader* shaders[2] = {&vs, &fs};
  R_ShaderPack program;
  R_ShaderPackInit(&program, shaders, 2);

  // Create the actual rendering pipeline.
  R_Attribute attribute;
  attribute.name = Str8Lit("Position");
  attribute.type = AttributeType_F2;

  R_Pipeline pipeline;
  R_PipelineInit(&pipeline, &program, &attribute, 1);
  R_PipelineAddBuffer(&pipeline, &vertex_buffer);
  R_PipelineAddBuffer(&pipeline, &index_buffer);

  Log("Starting game loop.", "");
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    // Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    R_PipelineBind(&pipeline);
    glDrawElements(
        GL_TRIANGLES, sizeof(indices) / sizeof(U32), GL_UNSIGNED_INT, (void*)0
    );

    glfwSwapBuffers(window);
    // Update
  }

  // Clean up after OpenGL
  R_BufferFreeGPU(&vertex_buffer);
  R_BufferFreeGPU(&index_buffer);

  R_ShaderFreeGPU(&vs);
  R_ShaderFreeGPU(&fs);
  R_ShaderPackFree(&program);

  R_PipelineFreeGPU(&pipeline);

  Log("Destroying window.", "");
  glfwDestroyWindow(window);
  Log("Terminating glfw.", "");
  glfwTerminate();
  ArenaRelease(&arena);
  return 0;
}