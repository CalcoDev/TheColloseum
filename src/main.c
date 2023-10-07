#include <glad/glad.h>
// seaprate so that glad is always first
#include <glfw/glfw3.h>
#include <stdio.h>

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

#include "draw/draw.h"

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

static F32 MoveSp      = 1.f;
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

  // ***************************************************************************
  // ** Resource Loading                                                      **
  // ***************************************************************************
  String8 input_path = OS_PathRelative(
      &arena, OS_PathExecutableDir(&arena), Str8Lit("./assets/data/input.toml")
  );

  I_InputMap input_map = {0};
  I_InputMapInit(&input_map, &arena, input_path);
  if (!I_InputMapSchemeSetActive(&input_map, "mouse_keyboard"))
    Log("Failed setting active input scheme!", "");
  if (!I_InputMapContextActivate(&input_map, "ingame"))
    Log("Failed setting active input context!", "");

  String8 atlas_path = OS_PathRelative(
      &arena, OS_PathExecutableDir(&arena),
      Str8Lit("./assets/sprites/atlas.png")
  );
  String8 atlas2_path = OS_PathRelative(
      &arena, OS_PathExecutableDir(&arena),
      Str8Lit("./assets/sprites/atlas2.png")
  );

  R_RenderInit(&window);
  D_Renderer renderer;
  D_RendererInit(&renderer, &arena);
  // R_Camera camera = R_CameraMakeOrthographic(
  //     Vec3F32_MultScalar(Vec3F32_Forward, -10.f), Vec3F32_Forward,
  //     Vec3F32_Up, 90.f, (F32)window.width / (F32)window.height, 0.1f, 100.f
  // );
  R_Camera camera = R_CameraMakePerspective(
      Vec3F32_MultScalar(Vec3F32_Forward, -10.f), Vec3F32_Forward, Vec3F32_Up,
      90.f, (F32)window.width / (F32)window.height, 1.f, 1000.f
  );
  R_Framebuffer framebuffer = R_FramebufferMake(
      160.f, 90.f, TextureWrap_ClampToEdge, TextureFilter_Nearest,
      TextureFormat_RGB, 1
  );

  R_Texture atlas, atlas2;
  R_TextureLoad(&atlas, atlas_path);
  R_TextureLoad(&atlas2, atlas2_path);

  // ***************************************************************************
  // ** Game Loop                                                             **
  // ***************************************************************************
  PrecisionTime elapsed_time      = 0;
  PrecisionTime prev_loop_time    = 0;
  PrecisionTime current_loop_time = 0;
  PrecisionTime delta_time        = 0;

  Log("Starting game loop.", "");

  F32 rot = 0.f;
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

      // Update
      {
        rot += 5.f;

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
      }

      // Render
      {
        R_FramebufferBind(&framebuffer);
        R_FramebufferSetViewport(&framebuffer);

        // i'll have to play around with depth buffers and alpha blending
        // atm it works but a bit scuffed and I'll abstract it.
        // as 2d requires different than 3d?
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        R_ClearDepthBuffer();
        R_ClearColourBuffer(0.2f, 0.1f, 0.3f);

        D_DrawBegin(&renderer);

        D_DrawTexturedQuad(
            &renderer, Vec3F32_Make(0.f, 0.f, 0.f), 0.f,
            Vec2F32_Make(64.f, 64.f), NULL, RectF32_Zero
        );

        D_DrawTexturedQuad(
            &renderer, Vec3F32_Make(0.f, 0.f, 0.f), 0.f,
            Vec2F32_Make(32.f, 18.f), &atlas,
            RectF32_Make(0.f, 16.f, 32.f, 18.f)
        );

        // D_DrawTexturedQuad(
        //     &renderer, Vec3F32_Make(0.f, 0.f, 0.f), F32_DegToRad(rot),
        //     Vec2F32_Make(16.f, 16.f), &atlas2,
        //     RectF32_Make(16.f, 0.f, 16.f, 16.f)
        // );

        D_DrawEnd(&renderer, &camera);
      }

      R_FramebufferBlitToScreenBuffer(&framebuffer, &window);
      R_RenderSwapchain(&window);
      prev_loop_time = current_loop_time;
    }
  }

  // ***************************************************************************
  // ** Cleanup                                                               **
  // ***************************************************************************
  D_RendererFree(&renderer);

  R_FramebufferFreeGPU(&framebuffer);
  OS_WindowFree(&window);
  ArenaRelease(&arena);
  return 0;
}