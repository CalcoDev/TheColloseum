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
  U32 handle;
} R_ShaderPack;

// NOTE(calco): Generic name pipeline, refers to a VAO in opengl?
typedef struct R_Pipeline
{
  // Shader
  R_ShaderPack* shader_pack;

  // VAO stuff
  R_Attribute* attributes;
  U64 attribute_count;
  U32 handle;

  // Internal state
  U64 _attrib; // # of attributes added
  U64 _bind;   // # of attributes bound
} R_Pipeline;

#endif