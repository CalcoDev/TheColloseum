#ifndef RENDER_H
#define RENDER_H

// NOTE(calco): This file is ordered in weird ways to make sure compilation and
// includes are properly handled.
// TODO(calco): Stop that from being the case.

#include "base/base_context.h"
#include "base/base_string.h"

// TODO(calco): remove this and refactor because this feels like bad inclusions
#include "os/os_window.h"

// NOTE(calco): -- Renderer Things --
void R_RenderInit(OS_Window* window);
void R_RenderSwapchain(OS_Window* window);

void R_ClearColourBuffer(F32 r, F32 g, F32 b);
void R_ClearDepthBuffer();

// NOTE(calco): -- Resource Things --
typedef enum R_BufferFlags
{
  BufferFlag_Null    = 0x0,
  BufferFlag_Dynamic = 0x1,

  // EXCLUSIVE; 0x2 0x4
  BufferFlag_Type_Vertex = 0x2,
  BufferFlag_Type_Index  = 0x4,
} R_BufferFlags;

typedef enum R_ShaderType
{
  ShaderType_Null     = 0x0,
  ShaderType_Vertex   = 0x1,
  ShaderType_Fragment = 0x2,
  ShaderType_Geometry = 0x4
} R_ShaderType;

typedef enum R_AttributeType
{
  AttributeType_Null = 0x0,
  AttributeType_F1   = 0x1,
  AttributeType_F2   = 0x2,
  AttributeType_F3   = 0x4,
  AttributeType_F4   = 0x8,
  AttributeType_S1   = 0x10,
  AttributeType_S2   = 0x20,
  AttributeType_S3   = 0x40,
  AttributeType_S4   = 0x80,
} R_AttributeType;

typedef struct R_Attribute
{
  String8 name;
  R_AttributeType type;
} R_Attribute;

typedef enum R_TextureWrap
{
  TextureWrap_Null              = 0x0,
  TextureWrap_ClampToEdge       = 0x1,
  TextureWrap_ClampToBorder     = 0x2,
  TextureWrap_Repeat            = 0x4,
  TextureWrap_MirroredRepeat    = 0x8,
  TextureWrap_MirrorClampToEdge = 0x10,
} R_TextureWrap;

typedef enum R_TextureFilter
{
  TextureFilter_Null                 = 0x0,
  TextureFilter_Nearest              = 0x1,
  TextureFilter_Linear               = 0x2,
  TextureFilter_LinearMipmapLinear   = 0x4,
  TextureFilter_LinearMipmapNearest  = 0x8,
  TextureFilter_NearestMipmapLinear  = 0x10,
  TextureFilter_NearestMipmapNearest = 0x20,
} R_TextureFilter;

typedef enum R_TextureFormat
{
  TextureFormat_Null         = 0x0,
  TextureFormat_RInteger     = 0x1,
  TextureFormat_R            = 0x2,
  TextureFormat_RG           = 0x4,
  TextureFormat_RGB          = 0x8,
  TextureFormat_RGBA         = 0x10,
  TextureFormat_DepthStencil = 0x20,
} R_TextureFormat;

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
R_Shader R_ShaderMake(Arena* arena, String8 path, R_ShaderType type);
void R_ShaderData(R_Shader* shader, String8 data);
void R_ShaderFreeGPU(R_Shader* shader);

// NOTE(calco): -- Shader Pack Functions --
// TODO(calco): I am not very certain about the R_Shader** thingy.
/**
 * @brief Initializes a shader pack.
 * @param pack The shader pack to initialize.
 * @param shaders A pointer to an array pointing to each of the shaders.
 * @param shader_count The amount of shaders to add.
 * @param arena The arena to allocate the uniform buffer hashmap on to
 * @param uniform_count The number of uniforms you wish to be cached.
 * @warning uniform_count should be a prime value, for better hashing!
 */
void R_ShaderPackInit(
    R_ShaderPack* pack, R_Shader** shaders, U64 shader_count, Arena* arena,
    U64 uniform_count
);
void R_ShaderPackFreeGPU(R_ShaderPack* pack);

void R_ShaderPackBind(R_ShaderPack* pack);

void R_ShaderPackUploadInt1(R_ShaderPack* pack, String8 name, S32 s1);
void R_ShaderPackUploadInt2(R_ShaderPack* pack, String8 name, S32 s1, S32 s2);
void R_ShaderPackUploadInt3(
    R_ShaderPack* pack, String8 name, S32 s1, S32 s2, S32 s3
);
void R_ShaderPackUploadInt4(
    R_ShaderPack* pack, String8 name, S32 s1, S32 s2, S32 s3, S32 s4
);

void R_ShaderPackUploadFloat1(R_ShaderPack* pack, String8 name, F32 f1);
void R_ShaderPackUploadFloat2(R_ShaderPack* pack, String8 name, F32 f1, F32 f2);
void R_ShaderPackUploadFloat3(
    R_ShaderPack* pack, String8 name, F32 f1, F32 f2, F32 f3
);
void R_ShaderPackUploadFloat4(
    R_ShaderPack* pack, String8 name, F32 f1, F32 f2, F32 f3, F32 f4
);

void R_ShaderPackUploadMat4(R_ShaderPack* pack, String8 name, F32** elements);

// NOTE(calco): -- Pipeline Functions --
void R_PipelineInit(
    R_Pipeline* pipeline, R_Attribute* attributes, U64 attribute_count
);
void R_PipelineAddBuffer(R_Pipeline* pipeline, R_Buffer* buffer);
void R_PipelineBind(R_Pipeline* pipeline);
void R_PipelineFreeGPU(R_Pipeline* pipeline);

// NOTE(calco): -- Textures --
void R_TextureInit(
    R_Texture* texture, U32 width, U32 height, R_TextureWrap wrap_s,
    R_TextureWrap wrap_t, R_TextureFilter filter_min,
    R_TextureFilter filter_mag, R_TextureFormat format, void* data
);
void R_TextureData(R_Texture* texture, void* data);
void R_TextureBind(R_Texture* texture, U32 slot);
void R_TextureFree(R_Texture* texture);

void R_TextureLoad(R_Texture* texture, String8 path);

// NOTE(calco): -- Framebuffers --
R_Framebuffer R_FramebufferMake(
    U32 width, U32 height, R_TextureWrap wrap, R_TextureFilter filter,
    R_TextureFormat format, B32 depth
);
void R_FramebufferInit(
    R_Framebuffer* framebuffer, U32 width, U32 height, R_Texture colour_texture,
    R_Texture depth_texture
);
void R_FramebufferBind(R_Framebuffer* framebuffer);
void R_FramebufferSetViewport(R_Framebuffer* framebuffer);
void R_FramebufferBindScreenBuffer();
void R_FramebufferBlitToScreenBuffer(
    R_Framebuffer* framebuffer, OS_Window* window
);

/**
 * @brief Frees up all GPU
 * @param framebuffer
 */
void R_FramebufferFreeGPU(R_Framebuffer* framebuffer);

#endif