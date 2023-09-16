#include <glad/glad.h>
// seaprate so that glad is always first
#include <glfw/glfw3.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "base/base_include.h"
#include "os/os.h"
#include "render/render.h"

void glfwErrorCallback(int code, const char* msg)
{
  LogError("glfw error: %s (%i)", msg, code);
}

// static F32 Inp_XAxis = 0.f;
// static F32 Inp_ZAxis = 0.f;
static F32 MoveSp = 0.05f;

void ProcessWindowInput(
    GLFWwindow* window, int key, int scancode, int action, int mods
)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  // if (action == GLFW_PRESS)
  // {
  //   if (key == GLFW_KEY_D)
  //     Inp_XAxis = 1.f;
  //   if (key == GLFW_KEY_A)
  //     Inp_XAxis = -1.f;

  //   if (key == GLFW_KEY_W)
  //     Inp_ZAxis = 1.f;
  //   if (key == GLFW_KEY_S)
  //     Inp_ZAxis = -1.f;
  // }

  // if (action == GLFW_RELEASE)
  // {
  //   if (key == GLFW_KEY_D)
  //     Inp_XAxis = 0.f;
  //   if (key == GLFW_KEY_A)
  //     Inp_XAxis = 0.f;

  //   if (key == GLFW_KEY_W)
  //     Inp_ZAxis = 0.f;
  //   if (key == GLFW_KEY_S)
  //     Inp_ZAxis = 0.f;
  // }
}

U64 hash_func(String8 key, U64 table_size)
{
  U64 hash   = 5381;
  U64 offset = 0;
  U8 c;

  while (offset < key.size)
  {
    c      = *(key.data + offset);
    hash   = ((hash << 5) + hash) + c;
    offset = offset + 1;
  }

  return hash % table_size;
}

B32 null_elem(HashmapEntry(String8, U64) entry)
{
  if (entry.key.size == 0)
    return 1;

  return 0;
}

int __main()
{
  // Vec2F32 l = Vec2F32_Left;
  // Vec2F32 u = Vec2F32_Up;

  // F32 d1 = Vec2F32_Dot(l, u);
  // F32 d2 = Vec2F32_Dot(Vec2F32_Right, Vec2F32_Down);
  // F32 d3 = Vec2F32_Dot(Vec2F32_Up, Vec2F32_Down);

  // Mat3x3F32 a = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
  // Mat3x3F32 b = {{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}}};
  // Mat3x3F32 c = Mat3x3_Mult(a, b);

  // Vec2F32 vec = Vec2F32_Make(10.f, 15.f);

  // Mat3x3F32 id     = Mat3x3_Identity();
  Mat3x3F32 t = Mat3x3_MakeTransform(Vec2F32_Make(2.f, -21.f));
  Mat3x3F32 r = Mat3x3_MakeRotation(F32_Pi * 0.5f);
  Mat3x3F32 s = Mat3x3_MakeScale(Vec2F32_Make(2.f, 2.f));

  Mat3x3F32 tr_s = Mat3x3_Mult(s, Mat3x3_Mult(t, r));
  Mat3x3F32 t_rs = Mat3x3_Mult(t, Mat3x3_Mult(r, s));

  return 0;

  // Mat3x3F32 final = Mat3x3_Mult(transf, Mat3x3_Mult(rot, scl));
  // Vec2F32 v       = Vec2F32_ApplyMatrix(final, vec);

  // Vec3F32 vec = Vec3F32_Make(10.f, 15.f, 0.f);

  // Mat4x4F32 id     = Mat4x4_Identity();
  // Mat4x4F32 transf = Mat4x4_MakeTranslate(Vec3F32_Make(2.f, 2.f, -69.f));
  // Mat4x4F32 rot    = Mat4x4_MakeRotation(Vec3F32_Forward, PiF32 * 0.5f);
  // Mat4x4F32 scl    = Mat4x4_MakeScale(Vec3F32_Make(2.f, 2.f, 2.f));

  // Mat4x4F32 final = Mat4x4_Mult(transf, Mat4x4_Mult(rot, scl));
  // Vec3F32 v       = Vec3F32_ApplyMatrix(final, vec);

  // Mat3x3F32 rot_scl = Mat3x3_Mult(rot, scl);
  // Mat3x3F32 scl_rot = Mat3x3_Mult(scl, rot);

  // Mat3x3F32 rot_scl_transf = Mat3x3_Mult(rot_scl, transf);
  // Mat3x3F32 transf_rot_scl = Mat3x3_Mult(transf, rot_scl);

  // Mat3x3F32 scl_rot_transf = Mat3x3_Mult(scl_rot, transf);
  // Mat3x3F32 transf_scl_rot = Mat3x3_Mult(transf, scl_rot);

  // Vec2F32 v1 = Vec2F32_ApplyMatrix(rot_scl_transf, vec);
  // Vec2F32 v2 = Vec2F32_ApplyMatrix(transf_rot_scl, vec);
  // Vec2F32 v3 = Vec2F32_ApplyMatrix(scl_rot_transf, vec);
  // Vec2F32 v4 = Vec2F32_ApplyMatrix(transf_scl_rot, vec);
}

int _main()
{
  OS_Init();

  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Megabytes(1));

  Hashmap(String8, U64) hash;
  HashmapInit(String8, U64, &arena, &hash, 17, hash_func, null_elem);

  HashmapAdd(String8, U64, &hash, Str8Lit("time"), 0);
  HashmapAdd(String8, U64, &hash, Str8Lit("hp"), 1);
  HashmapAdd(String8, U64, &hash, Str8Lit("blur"), 2);

  U64 v1 = HashmapGet(String8, U64, &hash, Str8Lit("time"));
  U64 v2 = HashmapGet(String8, U64, &hash, Str8Lit("hp"));
  U64 v3 = HashmapGet(String8, U64, &hash, Str8Lit("blur"));

  U64 v1_p;
  U64 v2_p;
  U64 v3_p;

  B32 b1 = HashmapTryGet(String8, U64, &hash, Str8Lit("time"), &v1_p);
  B32 b2 = HashmapTryGet(String8, U64, &hash, Str8Lit("hp"), &v2_p);
  B32 b3 = HashmapTryGet(String8, U64, &hash, Str8Lit("blur"), &v3_p);

  B32 b4 = HashmapTryGet(String8, U64, &hash, Str8Lit("no1"), &v1_p);
  B32 b5 = HashmapTryGet(String8, U64, &hash, Str8Lit("no2"), &v2_p);
  B32 b6 = HashmapTryGet(String8, U64, &hash, Str8Lit("blue"), &v3_p);

  ArenaRelease(&arena);
  return 0;
}

int main()
{
  // NOTES(calco): Init Memory
  OS_Init();

  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Gigabytes(1));

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

  // U32 window_width  = 800;
  // U32 window_height = 800;

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
      0.5f, 0.5f, 0.5f,    // 0
      1.0f, 1.0f,          // tex coords
                           //
      -0.5f, 0.5f, -0.5f,  // 1
      1.0f, -1.0f,         // tex coords
                           //
      -0.5f, 0.5f, 0.5f,   // 2
      -1.0f, -1.0f,        // tex coords
                           //
      0.5f, -0.5f, -0.5f,  // 3
      -1.0f, 1.0f,         // tex coords
                           //
      -0.5f, -0.5f, -0.5f, // 4
      -1.0f, 1.0f,         // tex coords
                           //
      0.5f, 0.5f, -0.5f,   // 5
      -1.0f, 1.0f,         // tex coords
                           //
      0.5f, -0.5f, 0.5f,   // 6
      -1.0f, 1.0f,         // tex coords
                           //
      -0.5f, -0.5f, 0.5f,  // 7
      -1.0f, 1.0f,         // tex coords
  };
  U32 indices[] = {
      0, 1, 2, //
      1, 3, 4, //
      5, 6, 3, //
      7, 3, 6, //
      2, 4, 7, //
      0, 7, 6, //
      0, 5, 1, //
      1, 5, 3, //
      5, 0, 6, //
      7, 4, 3, //
      2, 1, 4, //
      0, 2, 7  //
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
  vertex_attribs[1].name = Str8Lit("TexCoord");
  vertex_attribs[1].type = AttributeType_F2;

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

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);

  // Data for transforms.
  Vec3F32 translate = Vec3F32_MultScalar(
      Vec3F32_Forward, 2.f
  ); // Vec3F32_Make(0.2f, 0.5f, 0.f);

  Vec3F32 rotation_axis = Vec3F32_Up;
  F32 rotation_radians  = F32_Pi * 0.5f;

  Vec3F32 scale = Vec3F32_Make(1.f, 1.f, 1.f);

  F32 alpha        = 90.f;
  F32 halfAlhpaTan = F32_Tan(F32_DegToRad(alpha * 0.5f));
  F32 d            = 1 / halfAlhpaTan;

  F32 aspect_ratio = (F32)window_width / (F32)window_height;

  F32 clip_near = 0.003f;
  F32 clip_far  = 1000.f;

  // Calculate A and B to map [clip_near, clip_far] to [-1, 1], as opengl says
  // F32 a = (-clip_far - clip_near) / (clip_near - clip_far);
  // F32 b = (2.f * clip_far * clip_near) / (clip_near - clip_far);

  F32 a = 1.f - ((-2.f * clip_near) / (clip_far - clip_near));
  F32 b = (-2.f * clip_far * clip_near) / (clip_far - clip_near);

  /*

  Small explanation on coordinate systems:
  1. Local / Model Coordinates.
  The default thing when modeling, blender for example.

  2. World coordinates
  What I am used to seeing in Unity or Godot and shi... stuff.

  3. Camera Coordinates
  Converting world coords relative to camera in order to only have to calculate
  the camera view matrix thing ONCE.

  4. Clip Coordinates
  Ooga booga yes.

  5. Normalized Device Coordinaes
  Aka clip space becomes -1 1 range

  6. Viewport
  into the window thy go.

  1 2 and 3 are usually put togehter to create the MVP / WVP

  */

  // projection aka the P
  Mat4x4F32 projection      = Mat4x4_Identity();
  projection.elements[0][0] = d / aspect_ratio;
  projection.elements[1][1] = d;

  // Move Z into W
  projection.elements[3][3] = 0.f;
  projection.elements[3][2] = 1.f;

  // Clip
  projection.elements[2][2] = b;
  projection.elements[2][3] = a;

  Vec3F32 camera_pos = Vec3F32_Make(0.f, 0.f, 0.f);
  Vec3F32 camera_u   = Vec3F32_Right;
  Vec3F32 camera_v   = Vec3F32_Up;
  Vec3F32 camera_n   = Vec3F32_Forward;

  Log("Starting game loop.", "");
  while (!glfwWindowShouldClose(window))
  {
    current_loop_time = OS_TimeMicroseconds();
    delta_time        = current_loop_time - prev_loop_time;
    elapsed_time      = elapsed_time + delta_time;

    // 60 FPS, both render and update
    if (delta_time > 16000)
    {
      glfwPollEvents();

      // Update Game Logic
      // Log("Updated: %u!\nTime between frames: %u", current_loop_time,
      //     delta_time);

      Vec2F32 inp = {0};
      inp.x       = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) -
              (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
      inp.y = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) -
              (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
      inp = Vec2F32_Normalize(inp);

      Log("Normalized: (%.2f, %.2f)", inp.x, inp.y);

      Vec3F32 x_axis = Vec3F32_MultScalar(
          Vec3F32_Normalize(Vec3F32_Cross(camera_v, camera_n)), inp.x * MoveSp
      );
      Vec3F32 z_axis = Vec3F32_MultScalar(
          Vec3F32_Normalize(Vec3F32_Cross(camera_v, camera_u)),
          -1.f * inp.y * MoveSp
      );

      // Log("XAxis - (%.2f, %.2f, %.2f).", x_axis.x, x_axis.y, x_axis.z);
      // Log("ZAxis - (%.2f, %.2f, %.2f).", z_axis.x, z_axis.y, z_axis.z);

      Vec3F32 movement = Vec3F32_Add(x_axis, z_axis);
      // Log("Movement - (%.2f, %.2f, %.2f).", movement.x, movement.y,
      // movement.z);

      camera_pos = Vec3F32_Add(camera_pos, movement);

      rotation_radians += delta_time / 1000.f / 500.f;
      if (F32_Abs(rotation_radians) > 2 * F32_Pi)
        rotation_radians = 0.f;

      // Log("Rotation radians: %.2f", rotation_radians);

      // MATRIX STUFF

      // world transform aka model projection M
      Mat4x4F32 world_transform = Mat4x4_Mult(
          Mat4x4_MakeTranslate(translate),
          Mat4x4_Mult(
              Mat4x4_MakeRotation(rotation_axis, rotation_radians),
              Mat4x4_MakeScale(scale)
          )
      );

      // camera transform aka view transform aka V
      Mat4x4F32 camera_transform = Mat4x4_MakeValue(0.f);

      // Set up transposed i and j hat for reverse camera
      camera_transform.elements[0][0] = camera_u.x;
      camera_transform.elements[0][1] = camera_u.y;
      camera_transform.elements[0][2] = camera_u.z;

      camera_transform.elements[1][0] = camera_v.x;
      camera_transform.elements[1][1] = camera_v.y;
      camera_transform.elements[1][2] = camera_v.z;

      camera_transform.elements[2][0] = camera_n.x;
      camera_transform.elements[2][1] = camera_n.y;
      camera_transform.elements[2][2] = camera_n.z;

      // Translate everything so that camera is 0, 0
      camera_transform.elements[0][3] = -camera_pos.x;
      camera_transform.elements[1][3] = -camera_pos.y;
      camera_transform.elements[2][3] = -camera_pos.z;

      // Keep depth buffer Z the same ???
      camera_transform.elements[3][3] = 1.f;

      // Could calc here, but usually passed to the shader.
      // Mat4x4F32 mvp = Mat4x4_Mult(
      //     projection, Mat4x4_Mult(camera_transform, world_transform)
      // );

      // MATRIX STUFF OVER

      // Render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      R_TextureBind(&texture, 0);
      R_PipelineBind(&pipeline);

      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("model"), world_transform.elements[0]
      );
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("view"), camera_transform.elements[0]
      );
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("projection"), projection.elements[0]
      );

      glDrawElements(
          GL_TRIANGLES, sizeof(indices) / sizeof(U32), GL_UNSIGNED_INT, (void*)0
      );

      glfwSwapBuffers(window);

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

  Log("Destroying window.", "");
  glfwDestroyWindow(window);
  Log("Terminating glfw.", "");
  glfwTerminate();
  ArenaRelease(&arena);
  return 0;
}