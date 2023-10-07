#ifndef DRAW_H
#define DRAW_H

#include "base/base_math.h"
#include "base/base_memory.h"
#include "base/base_types.h"

#include "render/camera/render_camera.h"
#include "render/render.h"

#define D_RENDERER_MAX_VERTICES_COUNT 1024
#define D_RENDERER_MAX_INDICES_COUNT  1024

// TODO(calco): READ THIS LOL
/*
by the way, you should use the Z buffer for your 2D depth testing only for
opaque objects, and you should still submit the draw calls for your sprites in
front-to-back order (as opposed to the intuitive back-to-front.) The reason is
that one sprite might be covering another sprite, and the GPU can often detect
this case using its Z buffer acceleration structures. In this way, you will
roughly only have to pay the pixel shading cost for sprites that are ultimately
visible.

On the other hand, if your objects are transparent, then you must draw them from
back to front, otherwise alpha blending will not give you the correct result.
This suggests that you should split your scene between opaque objects and
alpha-blended objects. Furthermore, on the topic of alpha blending, you should
be careful to correctly consider pre-multiplied alpha and SRGB conversion to
your sprites, otherwise your alpha blending and lighting computations will be
wrong.

With issues like the ones I mentioned, there is a considerable amount of
pre-processing on the sprites you want to render each frame. For example, you
should cull any sprites outside the camera's view, you should sort them by
opaque and transparent, sort them by front-to-back or back-to-front, sort them
based on the texture atlas they use, and so on. For these reasons, I suggest
refactoring your code to draw a batch of sprites, rather than drawing individual
quads. Sort your sprites into big batches, upload all their data up front, then
draw ranges of sprites data with their appropriate textures bound. That will
also greatly reduce the amount of OpenGL code in your project, since the GL code
only concerns itself with uploading the data and drawing it at render time,
rather than being spread around your codebase in the form of loosely coupled
draw calls and buffer bindings.

tl;dr: The devil is in the details.
*/

/**
 * @brief Used internally for handling the texture arrays.
 * @warning Should never exceed 7.
 */
#define D_RENDERER_MAX_TEXTURE_COUNT 7

typedef struct D_Vertex2D
{
  Vec3F32 position;
  Vec2F32 texture_coordinates;
  F32 texture_index;
} D_Vertex2D;

typedef struct D_Renderer
{
  Arena* arena;
  R_Pipeline pipeline;

  // TODO(calco): handle 3rd shader in free and add
  R_Shader shaders[3];
  R_ShaderPack shader_pack;

  R_Buffer vertex_buffer;
  R_Buffer index_buffer;

  D_Vertex2D vertices[D_RENDERER_MAX_VERTICES_COUNT];
  U32 indices[D_RENDERER_MAX_INDICES_COUNT];
  U32 vertex_count;
  U32 index_count;

  R_Texture texture_not_found;
  R_Texture* textures[D_RENDERER_MAX_TEXTURE_COUNT];
  U32 texture_count;
} D_Renderer;

void D_RendererInit(D_Renderer* renderer, Arena* arena);
void D_RendererFree(D_Renderer* renderer);

void D_DrawBegin(D_Renderer* renderer);

void D_DrawQuad(D_Renderer* renderer, Vec3F32 pos, F32 rotation, Vec2F32 scale);

/**
 * @brief Draws a textured quad to at specified world transform
 * @param renderer The renderer to use during rendering.
 * @param pos The centered position in world space of the quad.
 * @param rotation Angle in radians, in trigonometric sense.
 * @param scale The size of the quad in each direction.
 * @param texture The texture to index from. If NULL, renderer will use the
 * default texture_not_found texture.
 * @param uv The texture coordinates to use inside the texture.
 * @warning If texture is NULL, renderer will use the default texture_not_found
 * texture and reset the UVs accordingly.
 */
void D_DrawTexturedQuad(
    D_Renderer* renderer, Vec3F32 pos, F32 rotation, Vec2F32 scale,
    R_Texture* texture, RectF32 uv
);

void D_DrawEnd(D_Renderer* renderer, R_Camera* camera);

#endif