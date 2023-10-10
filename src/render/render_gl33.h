#ifndef RENDER_GL33_H
#define RENDER_GL33_H

#include "base/base_hashmap.h"
#include "base/base_types.h"
#include "render.h"

HashmapCreatePrototype(String8, U64);

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
  Hashmap(String8, U64) uniforms;
  U32 handle;
} R_ShaderPack;

// NOTE(calco): Generic name pipeline, refers to a VAO in opengl?
typedef struct R_Pipeline
{
  R_Attribute* attributes;
  U64 attribute_count;
  U32 handle;

  // Internal state
  U64 _attrib; // # of attributes added
  U64 _bind;   // # of attributes bound
} R_Pipeline;

// NOTE(calco): -- Textures --
typedef struct R_Texture
{
  U32 width;
  U32 height;

  R_TextureWrap wrap_s;
  R_TextureWrap wrap_t;

  R_TextureFilter filter_min;
  R_TextureFilter filter_mag;

  R_TextureFormat format;

  U32 handle;
} R_Texture;

typedef struct R_Framebuffer
{
  U32 width;
  U32 height;

  // TODO(calco): Add multiple colour attachments, for some odd reason?
  R_Texture colour_texture;
  R_Texture depth_texture;

  U32 handle;
} R_Framebuffer;

#endif