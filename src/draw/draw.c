#include "draw.h"

// TODO(calco): Make this not opengl specific.
#include <glad/glad.h>
//
#include <glfw/glfw3.h>

#include <stdlib.h>

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
  // String8 exe_path = OS_PathExecutableDir(arena);
  // String8 vs_path  = OS_PathRelative(
  //     arena, exe_path, Str8Lit("./assets/shaders/default_vert.vs")
  // );
  // String8 fs_path = OS_PathRelative(
  //     arena, exe_path, Str8Lit("./assets/shaders/default_frag.fs")
  // );

  // R_Shader vs = R_ShaderMake(arena, vs_path, ShaderType_Vertex);
  // R_Shader fs = R_ShaderMake(arena, fs_path, ShaderType_Fragment);

  // renderer->shaders[0] = vs;
  // renderer->shaders[1] = fs;

  // R_Shader* shader_ptrs[2] = {&vs, &fs};
  // TODO(calco) IMPORTANT PASSING WRONG VALUE: uniform_count is 2^5
  // R_ShaderPackInit(&renderer->shader_pack, shader_ptrs, 2, arena, 5);

  // Set up the rendering pipeline
  R_Attribute attribs[3];
  attribs[0].name = Str8Lit("pos");
  attribs[0].type = AttributeType_F3;
  attribs[1].name = Str8Lit("tex_coords");
  attribs[1].type = AttributeType_F2;
  attribs[2].name = Str8Lit("tex_idx");
  attribs[2].type = AttributeType_F1;

  R_PipelineInit(&renderer->pipeline, attribs, 3);
  R_PipelineAddBuffer(&renderer->pipeline, &renderer->vertex_buffer);
  R_PipelineAddBuffer(&renderer->pipeline, &renderer->index_buffer);

  renderer->vertex_count = 0;

  U8 texture_not_found_data[] = {217, 60, 240, 255, 0,   0,  0,   255,
                                 0,   0,  0,   255, 217, 60, 240, 255};
  R_TextureInit(
      &renderer->texture_not_found, 2, 2, TextureWrap_ClampToEdge,
      TextureWrap_ClampToEdge, TextureFilter_Nearest, TextureFilter_Nearest,
      TextureFormat_RGBA, texture_not_found_data
  );

  // TODO(calco): INIT ALL THE TEXTURES, MATERIALS AND BUCKETS
}

void D_RendererFree(D_Renderer* renderer)
{
  R_BufferFreeGPU(&renderer->vertex_buffer);
  R_BufferFreeGPU(&renderer->index_buffer);

  R_TextureFree(&renderer->texture_not_found);
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

  renderer->texture_count = 0;
  for (S32 i = 0; i < D_RENDERER_MAX_TEXTURE_COUNT; ++i)
    renderer->textures[i] = NULL;

  renderer->__buckets_count = 0;
  for (S32 i = 0; i < D_RENDERER_MAX_BUCKET_COUNT; ++i)
  {
    renderer->__buckets[i].depth       = 0;
    renderer->__buckets[i].material_id = 0;
    renderer->__buckets[i].translucent = 0;
    renderer->__buckets[i].size        = 0;
  }

  renderer->material_count = 0;
  for (S32 i = 0; i < 10; ++i)
    renderer->materials[i] = NULL;
}

/**
 * @brief Draw a quad of scale, rotated and centered around pos.
 */
void D_DrawQuad(
    D_Renderer* renderer, D_Material* material, Vec3F32 pos, F32 rotation,
    Vec2F32 scale
)
{
  // TODO(calco): Refactor material handling
  // Handle material
  {
    S32 index = -1;
    S32 i;
    for (i = 0; i < renderer->material_count; ++i)
    {
      // comapring materials by pointers as we check for same instance id.
      // SHOULD LATER BE HANDLED VIA ACTUAL MATERIAL.ID
      // TODO(calco): MATERIAL ID PROPERTY
      if (renderer->materials[i] == material)
      {
        index = i;
        break;
      }
    }
    if (index == -1 && renderer->material_count < 10)
    {
      renderer->material_count += 1;
      index                  = i;
      renderer->materials[i] = material;
    }
    if (index == -1)
    {
      index = 0;
      // TODO(calco): Create a default material lmao.
      LogError(
          "D_DrawQuad did not find a valid material. Something "
          "went "
          "wrong. Using renderer->material_not_found material.",
          ""
      );
    }

    // Add the things to the buckets array
    __D_SortMapPair p;
    p.translucent = !material->opaque;
    p.depth       = pos.z;
    p.material_id = index;
    p.offset      = renderer->index_count;
    p.size        = 6;

    renderer->__buckets[renderer->__buckets_count++] = p;
  }

  D_Vertex2D tl, tr, bl, br;
  F32 x, y;

  F32 cos = F32_Cos(rotation);
  F32 sin = F32_Sin(rotation);

  F32 half_x = scale.x * 0.5f;
  F32 half_y = scale.y * 0.5f;

  x           = (-half_x) * cos - (+half_y) * sin;
  y           = (-half_x) * sin + (+half_y) * cos;
  tl.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  //
  x           = (+half_x) * cos - (+half_y) * sin;
  y           = (+half_x) * sin + (+half_y) * cos;
  tr.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  //
  x           = (-half_x) * cos - (-half_y) * sin;
  y           = (-half_x) * sin + (-half_y) * cos;
  bl.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);
  //
  x           = (+half_x) * cos - (-half_y) * sin;
  y           = (+half_x) * sin + (-half_y) * cos;
  br.position = Vec3F32_Make(x + pos.x, y + pos.y, pos.z);

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
    D_Renderer* renderer, D_Material* material, Vec3F32 pos, F32 rotation,
    Vec2F32 scale, R_Texture* texture, RectF32 uv
)
{
  D_DrawQuad(renderer, material, pos, rotation, scale);

  S32 texture_index = -1;
  if (texture == NULL)
  {
    texture_index = 0;
    uv.x          = 0.f;
    uv.y          = 0.f;
    uv.w          = 2.f;
    uv.h          = 2.f;
  }
  else
  {
    S32 i;
    for (i = 0; i < renderer->texture_count; ++i)
    {
      if (renderer->textures[i]->handle == texture->handle)
      {
        texture_index = i + 1; // offset by 1 for texture_not_found
        break;
      }
    }
    if (texture_index == -1 &&
        renderer->texture_count < D_RENDERER_MAX_TEXTURE_COUNT)
    {
      renderer->texture_count += 1;
      texture_index         = i + 1; // offset by 1 for texture_not_found
      renderer->textures[i] = texture;
    }
    if (texture_index == -1)
    {
      texture_index = 0;
      LogError(
          "D_DrawTexturedQuad did not find a valid texture index. Something "
          "went "
          "wrong. Using renderer->texture_not_found texture.",
          ""
      );
    }
  }

  U32 vc                                   = renderer->vertex_count;
  renderer->vertices[vc - 4].texture_index = (F32)texture_index;
  renderer->vertices[vc - 3].texture_index = (F32)texture_index;
  renderer->vertices[vc - 2].texture_index = (F32)texture_index;
  renderer->vertices[vc - 1].texture_index = (F32)texture_index;

  Vec2F32 d = texture == NULL ? Vec2F32_Make(2.f, 2.f)
                              : Vec2F32_Make(texture->width, texture->height);
  renderer->vertices[vc - 4].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x, uv.y), d);
  renderer->vertices[vc - 3].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x + uv.w, uv.y), d);
  renderer->vertices[vc - 2].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x, uv.y + uv.h), d);
  renderer->vertices[vc - 1].texture_coordinates =
      Vec2F32_Div(Vec2F32_Make(uv.x + uv.w, uv.y + uv.h), d);
}

int compareBuckets(const void* a, const void* b)
{
  __D_SortMapPair da = *(__D_SortMapPair*)a;
  __D_SortMapPair db = *(__D_SortMapPair*)b;

  if (da.translucent != db.translucent)
    return da.translucent ? 1 : -1;

  if (F32_Abs(da.depth - db.depth) < 0.0001f)
    return (da.depth > db.depth ? 1 : -1) * (da.translucent ? 1 : -1);

  if (da.material_id != db.material_id)
    return da.material_id > db.material_id ? 1 : -1;

  return 0;
}

void D_DrawEnd(D_Renderer* renderer, R_Camera* camera)
{
  // TODO(calco): Look into setting the data with sub buffer something.

  R_PipelineBind(&renderer->pipeline);

  // TODO(calco): Sort renderer->buckets
  qsort(
      renderer->__buckets, renderer->__buckets_count, sizeof(__D_SortMapPair),
      compareBuckets
  );

  Log("Order after sort: %u, %u, %u\n", renderer->__buckets[0].offset / 6,
      renderer->__buckets[1].offset / 6, renderer->__buckets[2].offset / 6);

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

  // TODO(calco): Enable and disable depth sorting + transparency things
  S32 bound_material_id = -1;
  for (U32 i = 0; i < renderer->__buckets_count; ++i)
  {
    __D_SortMapPair bucket = renderer->__buckets[i];
    S32 material_id        = bucket.material_id;
    if (material_id != bound_material_id)
    {
      R_ShaderPackBind(renderer->materials[material_id]->shader);
      bound_material_id = material_id;
    }

    R_ShaderPackUploadMat4(
        renderer->materials[material_id]->shader, Str8Lit("view"),
        camera->view_matrix.elements[0]
    );
    R_ShaderPackUploadMat4(
        renderer->materials[material_id]->shader, Str8Lit("projection"),
        camera->projection_matrix.elements[0]
    );

    char name[] = "u_tex[0]";
    R_TextureBind(&renderer->texture_not_found, 0);
    R_ShaderPackUploadInt1(
        renderer->materials[material_id]->shader, Str8Init(name, 8), 0
    );
    for (U32 i = 0; i < renderer->texture_count; ++i)
    {
      R_TextureBind(renderer->textures[i], i + 1);
      name[6] = '0' + i + 1;
      R_ShaderPackUploadInt1(
          renderer->materials[material_id]->shader, Str8Init(name, 8), i + 1
      );
    }

    glDrawElements(
        GL_TRIANGLES, bucket.size, GL_UNSIGNED_INT,
        (void*)(bucket.offset * sizeof(U32))
    );
  }
}