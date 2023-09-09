#ifndef RENDER_GL33_H
#define RENDER_GL33_H

#include "base/base_types.h"
#include "render.h"

typedef struct R_Buffer
{
  R_BufferFlags flags;
  U32 handle;
} R_Buffer;

typedef struct R_Shader
{
  R_ShaderType type;
  U32 handle;
} R_Shader;

// NOTE(calco): Generic name shader pack, refers to a program in opengl.
typedef struct R_ShaderPack
{
  // TODO(calco): Vertex Array Object
  U32 handle;
} R_ShaderPack;

#endif