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

  LogFatal("conv_GetBufferType was provided an unknown buffer type!", "");
  return 0;
}

GLenum conv_GetBufferTypeDraw(R_BufferFlags flags)
{
  if (flags & BufferFlag_Dynamic)
    return GL_DYNAMIC_DRAW;
  else
    return GL_STATIC_DRAW;
}

GLenum conv_GetShaderType(R_ShaderType type)
{
  if (type & ShaderType_Vertex)
    return GL_VERTEX_SHADER;
  if (type & ShaderType_Fragment)
    return GL_FRAGMENT_SHADER;
  if (type & ShaderType_Geometry)
    return GL_GEOMETRY_SHADER;

  LogFatal("conv_GetShaderType was provided an unknown shader type!", "");
  return 0;
}

// NOTE(calco): -- Resource Functions --
// Implement the functions described in render.h

// NOTE(calco): -- Buffer Functions --
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

// NOTE(calco): -- Shader Functions --
void R_ShaderInit(R_Shader* shader, R_ShaderType type)
{
  shader->type   = type;
  shader->handle = glCreateShader(conv_GetShaderType(type));
}

void R_ShaderData(R_Shader* shader, String8 data)
{
  glShaderSource(shader->handle, 1, &data.data, NULL);
  glCompileShader(shader->handle);

  B32 success;
  char error_buffer[512];
  glGetShaderiv(shader->handle, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader->handle, 512, NULL, error_buffer);
    LogError(
        "Error occurred while compiling shader! OpenGL Info: %s", error_buffer
    );
  }
}

void R_ShaderFreeGPU(R_Shader* shader) { glDeleteShader(shader->handle); }

// NOTE(calco): -- Shader Pack Functions --
void R_ShaderPackInit(R_ShaderPack* pack, R_Shader** shaders, U64 shader_count)
{
  pack->handle = glCreateProgram();
  for (U64 i = 0; i < shader_count; ++i)
  {
    glAttachShader(pack->handle, (*(shaders + i))->handle);
  }

  glLinkProgram(pack->handle);

  // TODO(calco): Make this a macro somehow.
  B32 success;
  char error_buffer[512];
  glGetProgramiv(pack->handle, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(pack->handle, 512, NULL, error_buffer);
    LogError(
        "Error occurred while linking program! OpenGL Info: %s", error_buffer
    );
  }
}

// TODO(calco): Figure out if attached shaders should be deleted too.
void R_ShaderPackFree(R_ShaderPack* pack) { glDeleteProgram(pack->handle); }