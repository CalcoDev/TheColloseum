#ifndef DRAW_H
#define DRAW_H

#include "base/base_math.h"
#include "base/base_memory.h"
#include "base/base_types.h"

#include "render/camera/render_camera.h"
#include "render/render.h"

typedef struct D_Vertex2D
{
  Vec2F32 position;
  Vec2F32 texture_coordinates;
  S32 texture_index;
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
} D_Renderer;

void D_RendererInit(D_Renderer* renderer, Arena* arena);
void D_RendererFree(D_Renderer* renderer);

void D_DrawBegin(D_Renderer* renderer);
void D_DrawEnd(D_Renderer* renderer, R_Camera* camera);

#endif