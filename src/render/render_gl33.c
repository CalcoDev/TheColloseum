#include <glad/glad.h>
#include <stdio.h>

#include "base/base_log.h"
#include "render_gl33.h"

// NOTE(calco): -- Helper Functions --
// Translate the generic render.h enums and structs to backend specific things.
GLenum conv_GetBufferType(R_BufferFlags flags)
{
  if (flags & BufferFlag_Type_Vertex)
    return GL_ARRAY_BUFFER;
  if (flags & BufferFlag_Type_Index)
    return GL_ELEMENT_ARRAY_BUFFER;

  LogFatal("conv_GetBufferType was provided an incorrect buffer type.", "");
  return 0;
}

GLenum conv_GetBufferTypeDraw(R_BufferFlags flags)
{
  if (flags & BufferFlag_Dynamic)
    return GL_DYNAMIC_DRAW;
  else
    return GL_STATIC_DRAW;
}

// NOTE(calco): -- Resource Functions --
// Implement the functions described in render.h
void R_BufferInit(R_Buffer* buffer, R_BufferFlags flags)
{
  buffer->flags = flags;
  glGenBuffers(1, &buffer->handle);
}

void R_BufferData(R_Buffer* buffer, void* data, U64 size)
{
  GLenum buffer_type = conv_GetBufferType(buffer->flags);
  glBindBuffer(buffer_type, buffer->handle);
  glBufferData(buffer_type, size, data, conv_GetBufferTypeDraw(buffer->flags));
}

void R_BufferFreeGPU(R_Buffer* buffer) { glDeleteBuffers(1, &buffer->handle); }