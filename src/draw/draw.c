#include "draw.h"

// TODO(calco): Make this not opengl specific.
#include <glad/glad.h>
//
#include <glfw/glfw3.h>

#include "base/base_log.h"
#include "os/os.h"

void D_RendererInit(D_Renderer* renderer, Arena* arena)
{
  renderer->arena = arena;

  // Set up the buffers
  R_BufferInit(&renderer->vertex_buffer, BufferFlag_Type_Vertex);
  R_BufferInit(&renderer->index_buffer, BufferFlag_Type_Index);

  // Set up the shader
  // TODO(calco): Check if I can make this temp arena
  String8 exe_path = OS_PathExecutableDir(arena);
  String8 vs_path  = OS_PathRelative(
      arena, exe_path, Str8Lit("./assets/shaders/default_vert.vs")
  );
  String8 fs_path = OS_PathRelative(
      arena, exe_path, Str8Lit("./assets/shaders/default_frag.fs")
  );

  R_Shader vs = R_ShaderMake(arena, vs_path, ShaderType_Vertex);
  R_Shader fs = R_ShaderMake(arena, fs_path, ShaderType_Fragment);

  renderer->shaders[0] = vs;
  renderer->shaders[1] = fs;

  R_Shader* shader_ptrs[2] = {&vs, &fs};
  // TODO(calco) IMPORTANT PASSING WRONG VALUE: uniform_count is 2^5
  R_ShaderPackInit(&renderer->shader_pack, shader_ptrs, 2, arena, 5);

  // Set up the rendering pipeline
  R_Attribute attribs[3];
  attribs[0].name = Str8Lit("pos");
  attribs[0].type = AttributeType_F3;
  attribs[1].name = Str8Lit("tex_coords");
  attribs[1].type = AttributeType_F2;
  attribs[2].name = Str8Lit("tex_idx");
  attribs[2].type = AttributeType_F1;

  R_PipelineInit(&renderer->pipeline, &renderer->shader_pack, attribs, 3);
  R_PipelineAddBuffer(&renderer->pipeline, &renderer->vertex_buffer);
  R_PipelineAddBuffer(&renderer->pipeline, &renderer->index_buffer);

  renderer->vertex_count = 0;

  for (S32 i = 0; i < 9; ++i)
    renderer->textures[i] = NULL;
}

void D_RendererFree(D_Renderer* renderer)
{
  R_BufferFreeGPU(&renderer->vertex_buffer);
  R_BufferFreeGPU(&renderer->index_buffer);

  R_ShaderFreeGPU(&renderer->shaders[0]);
  R_ShaderFreeGPU(&renderer->shaders[1]);
  R_ShaderPackFreeGPU(&renderer->shader_pack);
  R_PipelineFreeGPU(&renderer->pipeline);
}

void D_DrawBegin(D_Renderer* renderer)
{
  for (U32 i = 0; i < renderer->vertex_count; ++i)
  {
    renderer->vertices[i].position            = Vec3F32_Zero;
    renderer->vertices[i].texture_coordinates = Vec2F32_Zero;
    renderer->vertices[i].texture_index       = 0;
  }

  renderer->vertex_count = 0;
  renderer->index_count  = 0;

  for (S32 i = 0; i < 9; ++i)
    renderer->textures[i] = NULL;
}

/**
 * @brief Draw a quad of scale, rotated and centered around pos.
 */
void D_DrawQuad(D_Renderer* renderer, Vec3F32 pos, F32 rotation, Vec2F32 scale)
{
  D_Vertex2D tl, tr, bl, br;
  F32 x, y;

  F32 cos = F32_Cos(rotation);
  F32 sin = F32_Sin(rotation);

  F32 half_x = scale.x * 0.5f;
  F32 half_y = scale.y * 0.5f;

  // TODO(calco): Set up default texcoords and texture indices

  //
  x = (-half_x) * cos - (+half_y) * sin;
  y = (-half_x) * sin + (+half_y) * cos;

  tl.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  // tl.texture_coordinates = Vec2F32_Make(0.f, 1.f);
  // tl.texture_index       = 1.f;

  //
  x = (+half_x) * cos - (+half_y) * sin;
  y = (+half_x) * sin + (+half_y) * cos;

  tr.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  // tr.texture_coordinates = Vec2F32_Make(1.f, 1.f);
  // tr.texture_index       = 1.f;

  //
  x = (-half_x) * cos - (-half_y) * sin;
  y = (-half_x) * sin + (-half_y) * cos;

  bl.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  // bl.texture_coordinates = Vec2F32_Make(0.f, 0.f);
  // bl.texture_index       = 1.f;

  //
  x = (+half_x) * cos - (-half_y) * sin;
  y = (+half_x) * sin + (-half_y) * cos;

  br.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  // br.texture_coordinates = Vec2F32_Make(1.f, 0.f);
  // br.texture_index       = 1.f;

  // Add them to the vertex buffer
  U32 vc = renderer->vertex_count;
  U32 ic = renderer->index_count;

  renderer->vertices[vc++] = tl; // vc - 4
  renderer->vertices[vc++] = tr; // vc - 3
  renderer->vertices[vc++] = bl; // vc - 2
  renderer->vertices[vc++] = br; // vc - 1
  renderer->vertex_count   = vc;

  // Add indices to index buffer
  renderer->indices[ic++] = vc - 4; // tl
  renderer->indices[ic++] = vc - 2; // bl
  renderer->indices[ic++] = vc - 1; // br

  renderer->indices[ic++] = vc - 1; // br
  renderer->indices[ic++] = vc - 3; // tr
  renderer->indices[ic++] = vc - 4; // tl
  renderer->index_count   = ic;
}

void D_DrawTexturedQuad(
    D_Renderer* renderer, Vec3F32 pos, F32 rotation, Vec2F32 scale,
    R_Texture* texture, RectF32 uv
)
{
  D_DrawQuad(renderer, pos, rotation, scale);

  S32 texture_index = -1;

  // TODO(calco): SCUFFED. Remove this loop and make it a hashmap.
  S32 i;
  for (i = 0; i < renderer->texture_count; ++i)
  {
    if (renderer->textures[i]->handle == texture->handle)
    {
      texture_index = i;
      break;
    }
  }
  if (texture_index == -1 && renderer->texture_count < 9)
  {
    texture_index         = i;
    renderer->textures[i] = texture;
  }
  if (texture_index == -1)
  {
    LogError(
        "D_DrawTexturedQuad did not find a valid texture index. Something went "
        "wrong. Using default purple texture.",
        ""
    );
  }

  U32 vc                                   = renderer->vertex_count;
  renderer->vertices[vc - 4].texture_index = (F32)texture_index;
  renderer->vertices[vc - 3].texture_index = (F32)texture_index;
  renderer->vertices[vc - 2].texture_index = (F32)texture_index;
  renderer->vertices[vc - 1].texture_index = (F32)texture_index;

  Vec2F32 d = Vec2F32_Make(texture->width, texture->height);
  renderer->vertices[vc - 4].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x, uv.y), d);
  renderer->vertices[vc - 3].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x + uv.w, uv.y), d);
  renderer->vertices[vc - 2].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x, uv.y + uv.h), d);
  renderer->vertices[vc - 1].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x + uv.w, uv.y + uv.h), d);
}

void D_DrawEnd(D_Renderer* renderer, R_Camera* camera)
{
  // TODO(calco): Look into setting the data with sub buffer something.

  R_PipelineBind(&renderer->pipeline);

  R_ShaderPackUploadMat4(
      renderer->pipeline.shader_pack, Str8Lit("view"),
      camera->view_matrix.elements[0]
  );
  R_ShaderPackUploadMat4(
      renderer->pipeline.shader_pack, Str8Lit("projection"),
      camera->projection_matrix.elements[0]
  );

  for (U32 i = 0; i < renderer->texture_count; ++i)
    R_TextureBind(renderer->textures[i], i);

  // Move the D_Vertex array to vertex buffer
  R_BufferData(
      &renderer->vertex_buffer, renderer->vertices,
      renderer->vertex_count * sizeof(renderer->vertices[0])
  );
  // Move the index array to index buffer
  R_BufferData(
      &renderer->index_buffer, renderer->indices,
      renderer->index_count * sizeof(renderer->indices[0])
  );

  glDrawElements(
      GL_TRIANGLES, renderer->index_count, GL_UNSIGNED_INT, (void*)0
  );
}