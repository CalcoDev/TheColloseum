#include <glad/glad.h>
// seaprate so that glad is always first
#include <glfw/glfw3.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "base/base_include.h"
#include "os/os.h"

#define OS_WINDOW_MAX_KEY_CALLBACK_SIZE            2
#define OS_WINDOW_MAX_MOUSE_BUTTON_CALLBACK_SIZE   2
#define OS_WINDOW_MAX_MOUSE_POSITION_CALLBACK_SIZE 2
#include "os/os_window.h"

#include "render/camera/render_camera.h"
#include "render/render.h"

#include "os/input/os_input.h"

#include "input/input.h"

U64 str_hash_t(CharPointer key, U64 table_size)
{
  uint64_t h  = 0x100;
  int32_t len = strlen(key);
  for (int32_t i = 0; i < len; i++)
  {
    h ^= key[i] & 255;
    h *= 1111111111111111111;
  }
  return h ^ h >> 32;
}

B32 str_null_t(HashmapEntryPointer(CharPointer, U8) entry)
{
  if (entry->key == '\0' || strlen(entry->key) == 0)
    return 1;

  return 0;
}

B32 str_elem_eq(
    HashmapEntryPointer(CharPointer, U8) e1,
    HashmapEntryPointer(CharPointer, U8) e2
)
{
  B32 both_null = (e1->key == '\0' && e2->key == '\0');
  B32 one_null  = (e1->key == '\0' && e2->key != '\0') ||
                 (e2->key == '\0' && e1->key != '\0');

  if (both_null)
    return 1;
  if (one_null)
    return 0;

  return strcmp(e1->key, e2->key) == 0;
}

static F32 MoveSp      = 0.25f;
static F32 Sensitivity = 0.15f;
static F32 Yaw         = -90.f;
static F32 Pitch       = 0.f;

static Vec2F32 MousePos = {0};
static F32 _lastX       = 0.f;
static F32 _lastY       = 0.f;

static Vec3F32 Input = {0};

void ProcessWindowInput(OS_Window* window, U32 key, OS_WindowKeyAction action)
{
  if (key == GLFW_KEY_ESCAPE && action == WindowKeyAction_Down)
    OS_WindowSetOpen(window, 0);
}

void CursorPositionCallback(OS_Window* window, F32 x, F32 y)
{
  F32 xoff = (x - _lastX) * Sensitivity;
  F32 yoff = (_lastY - y) * Sensitivity;

  _lastX = x;
  _lastY = y;

  Yaw += xoff;
  Pitch += yoff;

  if (Pitch > 89.0f)
    Pitch = 89.0f;
  if (Pitch < -89.0f)
    Pitch = -89.0f;
}

void ScrollCallback(OS_Window* window, F32 x, F32 y)
{
  Log("Scrolled: (%.2f, %.2f)", x, y);
}

int main()
{
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Gigabytes(1));

  OS_Init();
  OS_Window window = {0};
  OS_WindowInit(&window, 1280, 720, Str8Lit("OS Window"));

  OS_WindowRegisterKeyCallback(&window, ProcessWindowInput);
  OS_WindowRegisterMousePositionCallback(&window, CursorPositionCallback);
  OS_WindowRegisterScrollCallback(&window, ScrollCallback);
  OS_WindowSetMouseVisibility(&window, WindowMouseVisibility_Disabled);

  String8 path = OS_PathRelative(
      &arena, OS_PathExecutableDir(&arena), Str8Lit("./assets/data/input.toml")
  );

  I_InputMap input_map = {0};
  I_InputMapInit(&input_map, &arena, path);
  if (!I_InputMapSchemeSetActive(&input_map, "mouse_keyboard"))
    Log("Failed setting active input scheme!", "");
  if (!I_InputMapContextActivate(&input_map, "ingame"))
    Log("Failed setting active input context!", "");

  R_RenderInit(&window);

  R_Camera camera = R_CameraMakePerspective(
      Vec3F32_MultScalar(Vec3F32_Forward, -10.f), Vec3F32_Forward, Vec3F32_Up,
      90.f, (F32)window.width / (F32)window.height, 0.1f, 100.f
  );
  //   R_Camera camera = R_CameraMakeOrthographic(
  //       Vec3F32_MultScalar(Vec3F32_Forward, -10.f), Vec3F32_Forward,
  //       Vec3F32_Up, 10.f, (F32)window.width / (F32)window.height, 0.1f, 100.f
  //   );

  R_Framebuffer framebuffer = R_FramebufferMake(
      320, 180, TextureWrap_ClampToEdge, TextureFilter_Nearest,
      TextureFormat_RGB, 1
  );

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
  R_Shader vs = R_ShaderMake(&arena, vs_path, ShaderType_Vertex);

  String8 fs_path = OS_PathRelative(
      &arena, exe_path, Str8Lit("./assets/shaders/default_frag.fs")
  );
  R_Shader fs = R_ShaderMake(&arena, fs_path, ShaderType_Fragment);

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

  Vec3F32 cube_positions[] = {
      Vec3F32_Make(0.f, 0.f, 0.f),
      Vec3F32_Make(0.f, 20.f, 15.f),
      Vec3F32_Make(32.f, -27.f, 0.f),
      Vec3F32_Make(-36.f, 0.f, -29.f),
  };

  Mat4x4F32 cube_rotations[] = {
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(0.f, 0.f, 0.f)),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(12.f, 106.f, 259.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(172.f, 206.f, 82.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(84.f, 29.f, 169.f)),
  };

  Vec3F32 cube_scales[] = {
      Vec3F32_Make(1.f, 1.f, 1.f),
      Vec3F32_Make(0.5f, 1.7f, 5.2f),
      Vec3F32_Make(2.5f, 8.f, 0.2f),
      Vec3F32_Make(1.f, 1.f, 1.f),
  };

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
      I_InputMapUpdate(&input_map);

      I_InputMapContextAction* m;
      if (I_InputMapActionTryGet(&input_map, "ingame", "move_x", &m))
        Input.x = m->value.range_1d.value;
      if (I_InputMapActionTryGet(&input_map, "ingame", "move_y", &m))
        Input.y = m->value.range_1d.value;
      if (I_InputMapActionTryGet(&input_map, "ingame", "move_z", &m))
        Input.z = m->value.range_1d.value;

      Input = Vec3F32_Normalize(Input);

      Vec3F32 x_axis = Vec3F32_MultScalar(
          Vec3F32_Cross(camera.forward, camera.up), Input.x * MoveSp
      );
      Vec3F32 y_axis   = Vec3F32_MultScalar(camera.up, Input.y * MoveSp);
      Vec3F32 z_axis   = Vec3F32_MultScalar(camera.forward, Input.z * MoveSp);
      Vec3F32 movement = Vec3F32_Add(Vec3F32_Add(x_axis, y_axis), z_axis);
      camera.position  = Vec3F32_Add(camera.position, movement);

      Vec3F32 direction;
      direction.x = F32_Cos(F32_DegToRad(Yaw)) * F32_Cos(F32_DegToRad(Pitch));
      direction.y = F32_Sin(F32_DegToRad(Pitch));
      direction.z = F32_Sin(F32_DegToRad(Yaw)) * F32_Cos(F32_DegToRad(Pitch));
      camera.forward = Vec3F32_Normalize(direction);

      R_CameraUpdateMatrices(&camera);

      // Render
      R_FramebufferBind(&framebuffer);
      R_FramebufferSetViewport(&framebuffer);
      glEnable(GL_DEPTH_TEST);

      glDepthMask(GL_TRUE);
      R_ClearDepthBuffer();
      R_ClearColourBuffer(0.2f, 0.1f, 0.3f);

      // R_TextureBind(&texture, 0);
      R_PipelineBind(&pipeline);

      // TODO(calco): Have this in a draw class.
      // For now manually sending camera data to shaders.
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("view"), camera.view_matrix.elements[0]
      );
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("projection"),
          camera.projection_matrix.elements[0]
      );

      for (U64 i = 0; i < 1; ++i)
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

      R_FramebufferBlitToScreenBuffer(&framebuffer, &window);

      R_RenderSwapchain(&window);
      prev_loop_time = current_loop_time;
    }
  }

  // Clean up after OpenGL
  R_BufferFreeGPU(&vertex_buffer);
  R_BufferFreeGPU(&index_buffer);

  R_ShaderFreeGPU(&vs);
  R_ShaderFreeGPU(&fs);
  R_ShaderPackFreeGPU(&program);

  R_PipelineFreeGPU(&pipeline);

  R_FramebufferFreeGPU(&framebuffer);

  OS_WindowFree(&window);

  ArenaRelease(&arena);
  return 0;
}