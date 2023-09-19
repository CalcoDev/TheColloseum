#include "render_camera.h"

R_Camera R_CameraMakePerspective(
    Vec3F32 pos, Vec3F32 look_at, Vec3F32 up, F32 fov, F32 aspect_ratio,
    F32 c_near, F32 c_far
)
{
  R_Camera persp_cam = {0};

  persp_cam.forward = Vec3F32_Normalize(Vec3F32_Sub(look_at, pos));
  persp_cam.up      = up;

  persp_cam.fov          = fov;
  persp_cam.aspect_ratio = aspect_ratio;
  persp_cam.clip_near    = c_near;
  persp_cam.clip_far     = c_far;

  persp_cam.position    = pos;
  persp_cam.view_matrix = Mat4x4_MakeLookAt(pos, look_at, up);
  persp_cam.projection_matrix =
      Mat4x4_MakeProjection(fov, aspect_ratio, c_near, c_far);

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

  camera->projection_matrix = Mat4x4_MakeProjection(
      camera->fov, camera->aspect_ratio, camera->clip_near, camera->clip_far
  );
}