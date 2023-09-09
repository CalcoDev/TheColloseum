#ifndef RENDER_H
#define RENDER_H

// NOTE(calco): This file is ordered in weird ways to make sure compilation and
// includes are properly handled.
// TODO(calco): Stop that from being the case.

#include "base/base_context.h"
#include "base/base_string.h"

// NOTE(calco): -- Resource Things --
typedef enum R_BufferFlags
{
  BufferFlag_Null        = 0x0,
  BufferFlag_Dynamic     = 0x1,
  BufferFlag_Type_Vertex = 0x2,
  BufferFlag_Type_Index  = 0x3,
} R_BufferFlags;

typedef enum R_ShaderType
{
  ShaderType_Null     = 0x0,
  ShaderType_Vertex   = 0x1,
  ShaderType_Fragment = 0x2,
  ShaderType_Geometry = 0x3
} R_ShaderType;

// NOTE(calco): -- Implementation --
#ifdef BASE_GRAPHICS_BACKEND_GL33
#  include "render_gl33.h"
#else
#  error Backend support not implemented.
#endif

// NOTE(calco): -- Buffer Functions --
void R_BufferInit(R_Buffer* buffer, R_BufferFlags flags);
void R_BufferData(R_Buffer* buffer, void* data, U64 size);
void R_BufferFreeGPU(R_Buffer* buffer);

// NOTE(calco): -- Shader Functions --
void R_ShaderInit(R_Shader* shader, R_ShaderType type);
void R_ShaderData(R_Shader* shader, String8 data);
void R_ShaderFreeGPU(R_Shader* shader);

// NOTE(calco): -- Shader Pack Functions --

// TODO(calco): I am not very certain about the R_Shader** thingy.
/**
 * @brief Initializes a shader pack.
 * @param pack The shader pack to initialize.
 * @param shaders A pointer to an array pointing to each of the shaders.
 * @param shader_count The amount of shaders to add.
 */
void R_ShaderPackInit(R_ShaderPack* pack, R_Shader** shaders, U64 shader_count);
void R_ShaderPackFree(R_ShaderPack* pack);

#endif