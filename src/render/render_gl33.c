#include <glad/glad.h>
//
#include <glfw/glfw3.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "base/base_log.h"
#include "os/os.h"
#include "os/os_window.h"
#include "render_gl33.h"

// HashmapImplement(String8, U64);

void HashmapString8ToU64Init(
    Arena* arena, HashmapString8ToU64* hashmap, U64 exponent,
    HashmapString8ToU64Function hashfunction,
    HashmapString8ToU64NullElementFunction nullelemfunction,
    HashmapString8ToU64EqualElementFunction equalelemfunction
)
{
  hashmap->exponent     = exponent;
  hashmap->bucketcount  = 1 << exponent;
  hashmap->used_buckets = 0;
  HashmapString8ToU64Entry* mem =
      ArenaPush(arena, hashmap->bucketcount * sizeof(HashmapString8ToU64Entry));
  hashmap->entries           = mem;
  hashmap->hashfunction      = hashfunction;
  hashmap->nullelemfunction  = nullelemfunction;
  hashmap->equalelemfunction = equalelemfunction;
}
void HashmapString8ToU64Add(
    HashmapString8ToU64* hashmap, HashmapString8ToU64Key key,
    HashmapString8ToU64Value value
)
{
  U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);
  HashmapString8ToU64Entry entry = {0};
  entry.value                    = value;
  entry.key                      = key;
  U64 i                          = hash;
  while (1)
  {
    i = __HashmapLookup(hash, hashmap->exponent, i);
    if (hashmap->nullelemfunction(hashmap->entries + i))
    {
      if ((U64)hashmap->used_buckets + 1 >= (U64)hashmap->bucketcount)
        return;
      hashmap->used_buckets += 1;
      *(hashmap->entries + i) = entry;
      return;
    }
    else if (hashmap->equalelemfunction(&entry, hashmap->entries + i))
    {
      return;
    }
  }
}
HashmapString8ToU64Value
HashmapString8ToU64Get(HashmapString8ToU64* hashmap, HashmapString8ToU64Key key)
{
  HashmapString8ToU64Entry entry = {0};
  entry.key                      = key;
  U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);
  U64 i    = hash;
  while (1)
  {
    i = __HashmapLookup(hash, hashmap->exponent, i);
    if (hashmap->nullelemfunction(hashmap->entries + i) ||
        hashmap->equalelemfunction(&entry, hashmap->entries + i))
    {
      return (hashmap->entries + i)->value;
    }
  }
}
B32 HashmapString8ToU64TryGet(
    HashmapString8ToU64* hashmap, HashmapString8ToU64Key key,
    HashmapString8ToU64Value* outvalue
)
{
  HashmapString8ToU64Entry entry = {0};
  entry.key                      = key;
  U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);
  U64 i    = hash;
  while (1)
  {
    i = __HashmapLookup(hash, hashmap->exponent, i);
    if (hashmap->nullelemfunction(hashmap->entries + i))
    {
      return 0;
    }
    else if (hashmap->equalelemfunction(&entry, hashmap->entries + i))
    {
      *outvalue = (hashmap->entries + i)->value;
      return 1;
    }
  }
}

// NOTE(calco): -- Renderer Things --
void R_RenderInit(OS_Window* window)
{
  Log("Initializing OpenGL 3.3 renderer.", "");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Mac

  glfwWindowHint(GLFW_DEPTH_BITS, 24);

  glfwMakeContextCurrent(window->handle);

  // Init glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    LogFatal("Error occured while initialising GLAD.", "");
    glfwTerminate();
    return -1;
  }
}

void R_RenderSwapchain(OS_Window* window) { glfwSwapBuffers(window->handle); }

void R_ClearColourBuffer(F32 r, F32 g, F32 b)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(r, g, b, 0.0f);
}

void R_ClearDepthBuffer() { glClear(GL_DEPTH_BUFFER_BIT); }

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

GLint conv_GetTextureInternalFormat(R_TextureFormat format)
{
  switch (format)
  {
    case TextureFormat_RInteger:
      return GL_R32I;
    case TextureFormat_R:
      return GL_R8;
    case TextureFormat_RG:
      return GL_RG8;
    case TextureFormat_RGB:
      return GL_RGB8;
    case TextureFormat_RGBA:
      return GL_RGBA8;
    case TextureFormat_DepthStencil:
      return GL_DEPTH24_STENCIL8;
  }

  LogFatal(
      "conv_GetTextureInternalFormat was provided an unknown format type!", ""
  );
  return 0;
}

GLenum conv_GetTextureFormat(R_TextureFormat format)
{
  switch (format)
  {
    case TextureFormat_RInteger:
      return GL_RED_INTEGER;
    case TextureFormat_R:
      return GL_RED;
    case TextureFormat_RG:
      return GL_RG;
    case TextureFormat_RGB:
      return GL_RGB;
    case TextureFormat_RGBA:
      return GL_RGBA;
    case TextureFormat_DepthStencil:
      return GL_DEPTH_STENCIL;
  }

  LogFatal("conv_GetTextureFormat was provided an unknown format type!", "");
  return 0;
}

GLenum conv_GetTextureDatatype(R_TextureFormat format)
{
  if (format == TextureFormat_DepthStencil)
  {
    return GL_UNSIGNED_INT_24_8;
  }

  return GL_UNSIGNED_BYTE;
}

GLint conv_GetTextureWrapType(R_TextureWrap wrap)
{
  switch (wrap)
  {
    case TextureWrap_ClampToEdge:
      return GL_CLAMP_TO_EDGE;
    case TextureWrap_ClampToBorder:
      return GL_CLAMP_TO_BORDER;
    case TextureWrap_Repeat:
      return GL_REPEAT;
    case TextureWrap_MirroredRepeat:
      return GL_MIRRORED_REPEAT;
  }

  LogFatal("conv_GetTextureWrapType was provided an unknown texture wrap!", "");
  return 0;
}

GLint conv_GetTextureFilter(R_TextureFilter filter)
{
  switch (filter)
  {
    case TextureFilter_Nearest:
      return GL_NEAREST;
    case TextureFilter_Linear:
      return GL_LINEAR;
  }

  LogFatal("conv_GetTextureFilter was provided an unknown texture filter!", "");
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

// TODO(calco): This should also take a path and do stuff
void R_ShaderInit(R_Shader* shader, R_ShaderType type)
{
  shader->type   = type;
  shader->handle = glCreateShader(conv_GetShaderType(type));
}

R_Shader R_ShaderMake(Arena* arena, String8 path, R_ShaderType type)
{
  R_Shader shader = {0};
  R_ShaderInit(&shader, type);

  String8 data = OS_FileRead(arena, path);
  R_ShaderData(&shader, data);

  return shader;
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

U64 string8_hash(String8 key, U64 table_size)
{
  uint64_t h  = 0x100;
  int32_t len = key.size;
  for (int32_t i = 0; i < len; i++)
  {
    h ^= key.data[i] & 255;
    h *= 1111111111111111111;
  }
  return h ^ h >> 32;
}

B32 hash_elem_null(HashmapEntryPointer(String8, U64) entry)
{
  if (entry->key.size == 0)
    return 1;

  return 0;
}

B32 hash_elem_eq(
    HashmapEntryPointer(String8, U64) e1, HashmapEntryPointer(String8, U64) e2
)
{
  B32 both_null = (e1->key.data == '\0' && e2->key.data == '\0');
  B32 one_null  = (e1->key.data == '\0' && e2->key.data != '\0') ||
                 (e2->key.data == '\0' && e1->key.data != '\0');

  if (both_null)
    return 1;
  if (one_null)
    return 0;

  return strcmp(e1->key.data, e2->key.data) == 0;
}

// NOTE(calco): -- Shader Pack Functions --
void R_ShaderPackInit(
    R_ShaderPack* pack, R_Shader** shaders, U64 shader_count, Arena* arena,
    U64 uniform_count
)
{
  // TODO(calco): uniform count should be a prime number, but enforced.

  // TODO(calco) IMPORTANT: Currently pasing uniform_count as exp. If it high,
  // it bad. Fix this to get the closest / nearest value.
  HashmapInit(
      String8, U64, arena, &pack->uniforms, uniform_count, string8_hash,
      hash_elem_null, hash_elem_eq
  );

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
void R_ShaderPackFreeGPU(R_ShaderPack* pack) { glDeleteProgram(pack->handle); }

U64 get_handle_shaderpack_loc(R_ShaderPack* pack, String8 name)
{
  U64 loc;
  if (!HashmapTryGet(String8, U64, &pack->uniforms, name, &loc))
  {
    loc = glGetUniformLocation(pack->handle, name.data);
    HashmapAdd(String8, U64, &pack->uniforms, name, loc);
  }
  return loc;
}

void R_ShaderPackUploadInt1(R_ShaderPack* pack, String8 name, S32 s1)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform1i(loc, s1);
}

void R_ShaderPackUploadInt2(R_ShaderPack* pack, String8 name, S32 s1, S32 s2)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform2i(loc, s1, s2);
}

void R_ShaderPackUploadInt3(
    R_ShaderPack* pack, String8 name, S32 s1, S32 s2, S32 s3
)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform3i(loc, s1, s2, s3);
}

void R_ShaderPackUploadInt4(
    R_ShaderPack* pack, String8 name, S32 s1, S32 s2, S32 s3, S32 s4
)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform4i(loc, s1, s2, s3, s4);
}

void R_ShaderPackUploadFloat1(R_ShaderPack* pack, String8 name, F32 f1)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform1f(loc, f1);
}

void R_ShaderPackUploadFloat2(R_ShaderPack* pack, String8 name, F32 f1, F32 f2)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform2f(loc, f1, f2);
}

void R_ShaderPackUploadFloat3(
    R_ShaderPack* pack, String8 name, F32 f1, F32 f2, F32 f3
)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform3f(loc, f1, f2, f3);
}

void R_ShaderPackUploadFloat4(
    R_ShaderPack* pack, String8 name, F32 f1, F32 f2, F32 f3, F32 f4
)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniform4f(loc, f1, f2, f3, f4);
}

/**
 * @brief Uploads a Mat4 to the shader program, if such a unifrom exists.
 * @param pack The shader program to check for the uniform's location.
 * @param name The name of the Mat4 in the shader.
 * @param elements A pointer to 16 32-bit floats, stored in row-major order!
 * @warning Elements are expected to be stored in row-major order NOT
 * column-major.
 */
void R_ShaderPackUploadMat4(R_ShaderPack* pack, String8 name, F32** elements)
{
  U64 loc = get_handle_shaderpack_loc(pack, name);
  glUniformMatrix4fv(loc, 1, GL_FALSE, elements);
}

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

// NOTE(calco): -- Textures --

void R_TextureInit(
    R_Texture* texture, U32 width, U32 height, R_TextureWrap wrap_s,
    R_TextureWrap wrap_t, R_TextureFilter filter_min,
    R_TextureFilter filter_mag, R_TextureFormat format, void* data
)
{
  texture->width      = width;
  texture->height     = height;
  texture->wrap_s     = wrap_s;
  texture->wrap_t     = wrap_t;
  texture->filter_min = filter_min;
  texture->filter_mag = filter_mag;
  texture->format     = format;

  glGenTextures(1, &texture->handle);
  glBindTexture(GL_TEXTURE_2D, texture->handle);
  glTexImage2D(
      GL_TEXTURE_2D, 0, conv_GetTextureInternalFormat(texture->format),
      texture->width, texture->height, 0,
      conv_GetTextureFormat(texture->format),
      conv_GetTextureDatatype(texture->format), data
  );

  AssertTrue(
      filter_mag == TextureFilter_Nearest || filter_mag == TextureFilter_Linear,
      "Texture Filter cannot be null!", ""
  );

  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, conv_GetTextureWrapType(texture->wrap_s)
  );
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, conv_GetTextureWrapType(texture->wrap_t)
  );
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      conv_GetTextureFilter(texture->filter_min)
  );
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
      conv_GetTextureFilter(texture->filter_mag)
  );
}

void R_TextureData(R_Texture* texture, void* data)
{
  glBindTexture(GL_TEXTURE_2D, texture->handle);
  glTexSubImage2D(
      GL_TEXTURE_2D, 0, 0, 0, texture->width, texture->height,
      conv_GetTextureFormat(texture->format),
      conv_GetTextureDatatype(texture->filter_mag), data
  );
}

void R_TextureBind(R_Texture* texture, U32 slot)
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void R_TextureFree(R_Texture* texture)
{
  glDeleteTextures(1, &texture->handle);
}

void R_TextureLoad(R_Texture* texture, String8 path)
{
  S32 x, y, channels;
  stbi_set_flip_vertically_on_load(0);
  char* data = stbi_load((const char*)path.data, &x, &y, &channels, 0);
  R_TextureInit(
      texture, x, y, TextureWrap_ClampToBorder, TextureWrap_ClampToBorder,
      TextureFilter_Nearest, TextureFilter_Nearest, TextureFormat_RGBA, data
  );
  stbi_image_free(data);
}

// NOTE(calco): -- Framebuffers --
R_Framebuffer R_FramebufferMake(
    U32 width, U32 height, R_TextureWrap wrap, R_TextureFilter filter,
    R_TextureFormat format, B32 depth
)
{
  R_Framebuffer framebuffer;

  R_Texture colour_texture = {0};
  R_TextureInit(
      &colour_texture, width, height, wrap, wrap, filter, filter, format, 0
  );

  R_Texture depth_texture = {0};
  if (depth)
  {
    R_TextureInit(
        &depth_texture, width, height, wrap, wrap, filter, filter,
        TextureFormat_DepthStencil, 0
    );
  }

  R_FramebufferInit(&framebuffer, width, height, colour_texture, depth_texture);
  return framebuffer;
}

void R_FramebufferInit(
    R_Framebuffer* framebuffer, U32 width, U32 height, R_Texture colour_texture,
    R_Texture depth_texture
)
{
  glGenFramebuffers(1, &framebuffer->handle);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);

  framebuffer->width  = width;
  framebuffer->height = height;

  framebuffer->colour_texture = colour_texture;
  R_TextureBind(&framebuffer->colour_texture, 0);
  glFramebufferTexture2D(
      GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      framebuffer->colour_texture.handle, 0
  );

  if (framebuffer->depth_texture.format != TextureFormat_Null)
  {
    framebuffer->depth_texture = depth_texture;
    R_TextureBind(&framebuffer->depth_texture, 0);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
        framebuffer->depth_texture.handle, 0
    );
  }
}

void R_FramebufferBind(R_Framebuffer* framebuffer)
{
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
}

void R_FramebufferSetViewport(R_Framebuffer* framebuffer)
{
  glViewport(0, 0, framebuffer->width, framebuffer->height);
}

void R_FramebufferBindScreenBuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void R_FramebufferBlitToScreenBuffer(
    R_Framebuffer* framebuffer, OS_Window* window
)
{
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer->handle);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(
      0, 0, framebuffer->width, framebuffer->height, 0, 0, window->width,
      window->height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST
  );

  // TODO(calco): Consider not using GL_NEAREST for upscaling the framebuffer?
}

void R_FramebufferFreeGPU(R_Framebuffer* framebuffer)
{
  if (framebuffer->colour_texture.format != TextureFormat_Null)
  {
    R_TextureFree(&framebuffer->colour_texture.handle);
  }

  if (framebuffer->depth_texture.format != TextureFormat_Null)
  {
    R_TextureFree(&framebuffer->depth_texture.handle);
  }

  glDeleteFramebuffers(1, &framebuffer->handle);
}