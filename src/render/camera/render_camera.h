#ifndef RENDER_CAMERA_H
#define RENDER_CAMERA_H

#include "base/base_math.h"

// TODO(calco): Handle this with some sort of uniform
// TODO(calco): Replace the position up and things with a "transform component"
typedef struct R_Camera
{
  Vec3F32 position;
  Vec3F32 forward;
  Vec3F32 up;

  F32 fov;
  F32 aspect_ratio;
  F32 clip_near;
  F32 clip_far;

  Mat4x4F32 view_matrix;
  Mat4x4F32 projection_matrix;
} R_Camera;

// NOTE(calco): -- Camera Function --
R_Camera R_CameraMakePerspective(
    Vec3F32 pos, Vec3F32 look_at, Vec3F32 up, F32 fov, F32 aspect_ratio,
    F32 c_near, F32 c_far
);

void R_CameraUpdateMatrices(R_Camera* camera);

#endif