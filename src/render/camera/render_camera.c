#include "render_camera.h"

// NOTE(calco): -- Camera Function --
R_Camera R_CameraMakeOrthographic(
    Vec3F32 pos, Vec3F32 forward, Vec3F32 up, F32 size, F32 aspect_ratio,
    F32 c_near, F32 c_far
)
{
  R_Camera ortho_cam       = {0};
  ortho_cam.is_ortographic = 1;

  ortho_cam.position = pos;
  ortho_cam.forward  = forward;
  ortho_cam.up       = up;

  ortho_cam.ortho_size   = size;
  ortho_cam.aspect_ratio = aspect_ratio;
  ortho_cam.clip_near    = c_near;
  ortho_cam.clip_far     = c_far;

  F32 right  = size * aspect_ratio * 0.5f;
  F32 left   = -right;
  F32 top    = size * 0.5f;
  F32 bottom = -top;

  ortho_cam.view_matrix = Mat4x4_MakeLookAt(pos, Vec3F32_Add(pos, forward), up);
  ortho_cam.projection_matrix =
      Mat4x4_MakeOrthographic(left, right, bottom, top, c_near, c_far);

  return ortho_cam;
}

R_Camera R_CameraMakePerspective(
    Vec3F32 pos, Vec3F32 forward, Vec3F32 up, F32 fov, F32 aspect_ratio,
    F32 c_near, F32 c_far
)
{
  R_Camera persp_cam       = {0};
  persp_cam.is_ortographic = 0;

  persp_cam.position = pos;
  persp_cam.forward  = forward;
  persp_cam.up       = up;

  persp_cam.fov          = fov;
  persp_cam.aspect_ratio = aspect_ratio;
  persp_cam.clip_near    = c_near;
  persp_cam.clip_far     = c_far;

  persp_cam.view_matrix = Mat4x4_MakeLookAt(pos, Vec3F32_Add(pos, forward), up);
  persp_cam.projection_matrix =
      Mat4x4_MakePerspective(fov, aspect_ratio, c_near, c_far);

  return persp_cam;
}

// TODO(calco): Actually do this lmao
void R_CameraUpdateMatrices(R_Camera* camera)
{
  // TODO(calco): Figure out if normalize should happen here.
  // camera->forward = Vec3F32_Normalize(camera->forward);
  // camera->up = Vec3F32_Normalize(camera->up);

  camera->view_matrix = Mat4x4_MakeLookAt(
      camera->position, Vec3F32_Add(camera->position, camera->forward),
      camera->up
  );

  if (camera->is_ortographic)
  {
    F32 half_size = camera->ortho_size * 0.5f;
    F32 right     = half_size * camera->aspect_ratio;
    F32 left      = -right;
    F32 top       = half_size;
    F32 bottom    = -top;

    camera->projection_matrix = Mat4x4_MakeOrthographic(
        left, right, bottom, top, camera->clip_near, camera->clip_far
    );
  }
  else
  {
    camera->projection_matrix = Mat4x4_MakePerspective(
        camera->fov, camera->aspect_ratio, camera->clip_near, camera->clip_far
    );
  }
}