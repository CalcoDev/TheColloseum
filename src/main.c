#include <glad/glad.h>
// seaprate so that glad is always first
#include <glfw/glfw3.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "base/base_include.h"
#include "os/os.h"
#include "os/os_window.h"
#include "render/render.h"

// Mouse and movement
void ProcessWindowInput(
    GLFWwindow* window, int key, int scancode, int action, int mods
)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

static F32 MoveSp      = 0.05f;
static F32 Sensitivity = 0.01f;
static F32 Yaw         = -90.f;
static F32 Pitch       = 0.f;

static Vec2F32 MousePos = {0};
static F32 _lastX       = 0.f;
static F32 _lastY       = 0.f;

void CursorPositionCallback(GLFWwindow* window, F64 d_xpos, F64 d_ypos)
{
  F32 xpos = (F32)d_xpos;
  F32 ypos = (F32)d_ypos;

  F32 xoff = (xpos - _lastX) * Sensitivity;
  F32 yoff = (_lastY - ypos) *
             Sensitivity; // inverted because window coords are inverted

  _lastX = xpos;
  _lastY = ypos;

  Yaw += xoff;
  Pitch += yoff;

  if (Pitch > 85.f)
    Pitch = 85.f;
  else if (Pitch < -85.f)
    Pitch = -85.f;
}

int main()
{
  // Set up memory
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Gigabytes(1));

  // Set up OS
  OS_Init();

  OS_Window window    = OS_WindowInit(1280, 720, Str8Lit("OS Window"));
  window.key_callback = ProcessWindowInput;

  R_RenderInit(&window);

  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Set up key callbacks.
  // glfwSetCursorPosCallback(window, CursorPositionCallback);

  // Data
  F32 vertices[] = {
      -1.0f, -1.0f, -1.0f, // 0
      1.0f,  0.0f,  0.0f,  // Red
      1.0f,  -1.0f, -1.0f, // 1
      0.0f,  1.0f,  0.0f,  // Green
      1.0f,  1.0f,  -1.0f, // 2
      0.0f,  0.0f,  1.0f,  // Blue
      -1.0f, 1.0f,  -1.0f, // 3
      1.0f,  1.0f,  0.0f,  // Yellow
      -1.0f, -1.0f, 1.0f,  // 4
      1.0f,  0.0f,  1.0f,  // Magenta
      1.0f,  -1.0f, 1.0f,  // 5
      0.0f,  1.0f,  1.0f,  // Cyan
      1.0f,  1.0f,  1.0f,  // 6
      1.0f,  1.0f,  1.0f,  // White
      -1.0f, 1.0f,  1.0f,  // 7
      0.0f,  0.0f,  0.0f   // Black
  };
  U32 indices[] = {
      0, 1, 2, 2, 3, 0, // Front
      4, 5, 6, 6, 7, 4, // Back
      1, 5, 6, 6, 2, 1, // Right
      0, 4, 7, 7, 3, 0, // Left
      3, 2, 6, 6, 7, 3, // Top
      0, 1, 5, 5, 4, 0  // Bottom
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
  R_ShaderPackInit(&program, shaders, 2, &arena, 7);

  // Create the actual rendering pipeline.
  R_Attribute vertex_attribs[2];
  vertex_attribs[0].name = Str8Lit("Position");
  vertex_attribs[0].type = AttributeType_F3;
  vertex_attribs[1].name = Str8Lit("Colour");
  vertex_attribs[1].type = AttributeType_F3;

  R_Pipeline pipeline;
  R_PipelineInit(&pipeline, &program, vertex_attribs, 2);
  R_PipelineAddBuffer(&pipeline, &vertex_buffer);
  R_PipelineAddBuffer(&pipeline, &index_buffer);

  // Some texture action lol
  String8 texture_path =
      OS_PathRelative(&arena, exe_path, Str8Lit("./assets/sprites/player.jpg"));

  S32 x, y, channels;
  stbi_set_flip_vertically_on_load(1);
  char* data = stbi_load((const char*)texture_path.data, &x, &y, &channels, 0);

  R_Texture texture;
  R_TextureInit(
      &texture, x, y, TextureWrap_ClampToEdge, TextureWrap_ClampToEdge,
      TextureFilter_Nearest, TextureFilter_Nearest, TextureFormat_RGB, NULL
  );

  R_TextureData(&texture, (void*)data);

  stbi_image_free(data);

  PrecisionTime elapsed_time      = 0;
  PrecisionTime prev_loop_time    = 0;
  PrecisionTime current_loop_time = 0;
  PrecisionTime delta_time        = 0;

  // Model Matrix (local to world)
  Mat4x4F32 model_matrix = Mat4x4_MakeValue(0.f);

  Vec3F32 translate = Vec3F32_Make(0.f, 0.f, 0.f);
  Vec3F32 scale     = Vec3F32_Make(1.f, 1.f, 1.f);
  Mat4x4F32 rotation =
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(0.f, 0.f, 0.f));

  // View Matrix / Camera
  Mat4x4F32 view_matrix = Mat4x4_MakeValue(0.f);

  Vec3F32 camera_pos = Vec3F32_Make(0.f, 0.f, -10.f);
  // Vec3F32 camera_forward = Vec3F32_Forward;
  Vec3F32 camera_up = Vec3F32_Up;

  // Projection Matrix
  Mat4x4F32 projection_matrix = Mat4x4_MakeValue(1.f);

  F32 half_fov     = F32_DegToRad(45.f);
  F32 aspect_ratio = (F32)window.width / (F32)window.height;
  F32 c_near       = 0.1f;
  F32 c_far        = 1000.f;

  projection_matrix.elements[0][0] = 1.f / (F32_Tan(half_fov) * aspect_ratio);
  projection_matrix.elements[1][1] = 1.f / (F32_Tan(half_fov));
  projection_matrix.elements[3][2] = -1.f;
  projection_matrix.elements[2][2] = -(c_far + c_near) / (c_far - c_near);
  projection_matrix.elements[2][3] = -(2.f * c_far * c_near) / (c_far - c_near);
  projection_matrix.elements[3][3] = 0.f;

  // projection_matrix = Mat4x4_Transpose(projection_matrix);

  // F32 rotation_radians = 0.f;

  Vec3F32 cube_positions[] = {
      Vec3F32_Make(0.f, 0.f, 0.f),
      Vec3F32_Make(0.f, 20.f, 15.f),
      Vec3F32_Make(32.f, -27.f, 0.f),
      Vec3F32_Make(-36.f, 0.f, -29.f),
  };

  Mat4x4F32 cube_rotations[] = {
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(247.f, 128.f, 59.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(12.f, 106.f, 259.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(172.f, 206.f, 82.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(84.f, 29.f, 169.f)),
  };

  Vec3F32 cube_scales[] = {
      Vec3F32_Make(1.f, 2.3f, 0.4f),
      Vec3F32_Make(0.5f, 1.7f, 5.2f),
      Vec3F32_Make(2.5f, 8.f, 0.2f),
      Vec3F32_Make(1.f, 1.f, 1.f),
  };

  // Framebuffer
  GLuint _framebuffer = 0;
  glGenFramebuffers(1, &_framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

  R_Texture _texture;
  R_TextureInit(
      &_texture, 3200, 1800, TextureWrap_ClampToEdge, TextureWrap_ClampToEdge,
      TextureFilter_Nearest, TextureFilter_Nearest, TextureFormat_RGB, 0
  );

  GLuint _depth_buffer;
  glGenRenderbuffers(1, &_depth_buffer);
  glBindRenderbuffer(GL_RENDERBUFFER, _depth_buffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 3200, 1800);
  glFramebufferRenderbuffer(
      GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth_buffer
  );

  glFramebufferTexture(
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _texture.handle, 0
  );

  GLenum draw_buffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, draw_buffers);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    LogFatal("aaaaaaaaaa", "");
  }

  Log("Starting game loop.", "");
  while (OS_WindowIsOpen(&window))
  {
    current_loop_time = OS_TimeMicroseconds();
    delta_time        = current_loop_time - prev_loop_time;
    elapsed_time      = elapsed_time + delta_time;

    // 60 FPS, both render and update
    if (delta_time > 16000)
    {
      OS_WindowPollEvents();

      // View Matrix
      camera_pos.x = sin(glfwGetTime()) * 40.f;
      camera_pos.y = 20.f;
      camera_pos.z = cos(glfwGetTime()) * 40.f;

      view_matrix = Mat4x4_MakeLookAt(camera_pos, Vec3F32_Zero, camera_up);
      view_matrix = Mat4x4_Transpose(view_matrix);

      // Render
      glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
      glViewport(0, 0, 3200, 1800);

      glEnable(GL_DEPTH_TEST);

      // glEnable(GL_CULL_FACE);
      // glCullFace(GL_FRONT);
      // glFrontFace(GL_CCW);

      glDepthMask(GL_TRUE);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

      // R_TextureBind(&texture, 0);
      R_PipelineBind(&pipeline);

      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("view"), view_matrix.elements[0]
      );
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("projection"),
          projection_matrix.elements[0]
      );

      for (U64 i = 0; i < 4; ++i)
      {
        // Model Matrix
        model_matrix = Mat4x4_Mult(
            Mat4x4_MakeTranslate(Vec3F32_Add(translate, cube_positions[i])),
            Mat4x4_Mult(
                Mat4x4_Mult(rotation, cube_rotations[i]),
                Mat4x4_MakeScale(Vec3F32_Add(scale, cube_scales[i]))
            )
        );

        R_ShaderPackUploadMat4(
            pipeline.shader_pack, Str8Lit("model"), model_matrix.elements[0]
        );

        glDrawElements(
            GL_TRIANGLES, sizeof(indices) / sizeof(U32), GL_UNSIGNED_INT,
            (void*)0
        );
      }

      // Bind the source framebuffer
      glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer);
      // Bind the default framebuffer (the screen)
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

      glBlitFramebuffer(
          0, 0, 3200, 1800, 0, 0, 1280, 1080, GL_COLOR_BUFFER_BIT, GL_NEAREST
      );

      // Unbind the framebuffers (if necessary)
      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

      R_RenderSwapchain(&window);
      prev_loop_time = current_loop_time;
    }
  }

  // Clean up after OpenGL
  R_BufferFreeGPU(&vertex_buffer);
  R_BufferFreeGPU(&index_buffer);

  R_ShaderFreeGPU(&vs);
  R_ShaderFreeGPU(&fs);
  R_ShaderPackFree(&program);

  R_PipelineFreeGPU(&pipeline);

  OS_WindowFree(&window);

  ArenaRelease(&arena);
  return 0;
}