#ifndef RENDER_H
#define RENDER_H

// NOTE(calco): This file is ordered in weird ways to make sure compilation and
// includes are properly handled.
// TODO(calco): Stop that from being the case.

#include "base/base_context.h"

// NOTE(calco): -- Resource Things --
typedef enum R_BufferFlags
{
  BufferFlag_Dynamic     = 0x1,
  BufferFlag_Type_Vertex = 0x2,
  BufferFlag_Type_Index  = 0x3,
} R_BufferFlags;

typedef enum R_ShaderType
{
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

// NOTE(calco): -- Functions --
void R_BufferInit(R_Buffer* buffer, R_BufferFlags flags);
void R_BufferData(R_Buffer* buffer, void* data, U64 size);

#endif