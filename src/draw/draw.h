#ifndef DRAW_H
#define DRAW_H

#include "base/base_math.h"
#include "base/base_memory.h"
#include "base/base_types.h"

#include "render/camera/render_camera.h"
#include "render/render.h"

#define D_RENDERER_MAX_VERTICES_COUNT 1024
#define D_RENDERER_MAX_INDICES_COUNT  1024

typedef struct D_Vertex2D
{
  Vec3F32 position;
  Vec2F32 texture_coordinates;
  F32 texture_index;
} D_Vertex2D;

typedef struct D_Renderer
{
  Arena* arena;

  R_Pipeline pipeline;

  // TODO(calco): handle 3rd shader in free and add
  R_Shader shaders[3];
  R_ShaderPack shader_pack;

  R_Buffer vertex_buffer;
  R_Buffer index_buffer;

  D_Vertex2D vertices[D_RENDERER_MAX_VERTICES_COUNT];
  U32 indices[D_RENDERER_MAX_INDICES_COUNT];

  U32 vertex_count;
  U32 index_count;

  // TODO(calco): Maybe make this not a pointer, and free on end?
  R_Texture* texture;
} D_Renderer;

void D_RendererInit(D_Renderer* renderer, Arena* arena);
void D_RendererFree(D_Renderer* renderer);

void D_DrawBegin(D_Renderer* renderer);

void D_DrawQuad(D_Renderer* renderer, Vec3F32 pos, F32 rotation, Vec2F32 scale);
void D_DrawTexturedQuad(
    D_Renderer* renderer, Vec3F32 pos, F32 rotation, Vec2F32 scale,
    R_Texture* texture, RectF32 uv
);

void D_DrawEnd(D_Renderer* renderer, R_Camera* camera);

#endif