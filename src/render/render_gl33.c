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

GLint conv_GetAttributeTypeCount(R_AttributeType type)
{
  if (type & (AttributeType_F1 | AttributeType_S1))
    return 1;
  if (type & (AttributeType_F2 | AttributeType_S2))
    return 2;
  if (type & (AttributeType_F3 | AttributeType_S3))
    return 3;
  if (type & (AttributeType_F4 | AttributeType_S4))
    return 4;

  LogFatal(
      "conv_GetAttributeTypeCount was provided an unknown attribute type!", ""
  );
  return 0;
}

GLenum conv_GetAttributeTypeType(R_AttributeType type)
{
  if (type & (AttributeType_F1 | AttributeType_F2 | AttributeType_F3 |
              AttributeType_F4))
    return GL_FLOAT;
  if (type & (AttributeType_S1 | AttributeType_S2 | AttributeType_S3 |
              AttributeType_S4))
    return GL_INT;

  LogFatal(
      "conv_GetAttributeTypeType was provided an unknown attribute type!", ""
  );
  return 0;
}

U64 conv_GetAttributeTypeByteSize(R_AttributeType type)
{
  GLenum ttype = conv_GetAttributeTypeType(type);
  GLint size   = conv_GetAttributeTypeCount(type);

  return (ttype == GL_FLOAT ? sizeof(F32) : sizeof(S32)) * (U64)size;
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

// NOTE(calco): -- Pipeline Functions --
/**
 * @brief Sets up the pipeline data.
 * @warning Does not add any sort of attributes to the list by default! Please
 * use R_PipelineAddBuffer(...) to finish setup.
 * @param pipeline The pipeline to initialize.
 * @param shader_pack A linked and compiled shader pack to use for this
 * pipeline.
 * @param attribute_count The number of attributes in the attributes array.
 * @param attributes An array of attributes.
 */
void R_PipelineInit(
    R_Pipeline* pipeline, R_ShaderPack* shader_pack, R_Attribute* attributes,
    U64 attribute_count
)
{
  pipeline->shader_pack     = shader_pack;
  pipeline->attributes      = attributes;
  pipeline->attribute_count = attribute_count;
  pipeline->_attrib         = 0;
  pipeline->_bind           = 0;
  glGenVertexArrays(1, &pipeline->handle);
}

void R_PipelineAddBuffer(R_Pipeline* pipeline, R_Buffer* buffer)
{
  // Bind the VAO
  glBindVertexArray(pipeline->handle);

  if (buffer->flags & BufferFlag_Type_Vertex)
  {
    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, buffer->handle);

    // Set up the VAO
    U64 stride = 0;
    for (U64 i = pipeline->_attrib; i < pipeline->attribute_count; ++i)
    {
      stride += conv_GetAttributeTypeByteSize((pipeline->attributes + i)->type);
    }

    U64 offset = 0;
    for (U64 i = pipeline->_attrib; i < pipeline->attribute_count; ++i)
    {
      R_Attribute* attrib = (pipeline->attributes + i);
      GLint element_count = conv_GetAttributeTypeCount(attrib->type);
      GLenum type         = conv_GetAttributeTypeType(attrib->type);
      glVertexAttribPointer(
          i, element_count, type, GL_FALSE, stride, (void*)offset
      );
      glEnableVertexAttribArray(i);

      offset += conv_GetAttributeTypeByteSize((pipeline->attributes + i)->type);
    }
  }
  else if (buffer->flags & BufferFlag_Type_Index)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->handle);
  }

  // TODO(calco): Why do we use pipeline->_attrib ??????
}

void R_PipelineBind(R_Pipeline* pipeline)
{
  glUseProgram(pipeline->shader_pack->handle);
  glBindVertexArray(pipeline->handle);
}

void R_PipelineFreeGPU(R_Pipeline* pipeline)
{
  glDeleteVertexArrays(1, &pipeline->handle);
}