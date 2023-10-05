#include "draw.h"

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
  R_ShaderPackInit(&renderer->shader_pack, shader_ptrs, 2, &arena, 5);

  // Set up the rendering pipeline
  R_Attribute attribs[3];
  attribs[0].name = Str8Lit("Position");
  attribs[0].type = AttributeType_F2;
  attribs[1].name = Str8Lit("TexCoords");
  attribs[1].type = AttributeType_F2;
  attribs[2].name = Str8Lit("TexIndex");
  attribs[2].type = AttributeType_S1;

  R_PipelineInit(&renderer->pipeline, &renderer->shader_pack, attribs, 3);
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
  // TODO(calco): Actually do something here.
}

void D_DrawEnd(D_Renderer* renderer, R_Camera* camera)
{
  // TODO(calco): Actually do something here.

  /*

        R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("view"), camera.view_matrix.elements[0]
      );
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("projection"),
          camera.projection_matrix.elements[0]
      );

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

  */
}