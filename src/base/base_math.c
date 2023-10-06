#include "base_math.h"

// NOTE(calco): -- Base Math --
F32 F32_Abs(F32 f)
{
  if (f < 0)
    return -f;

  return f;
}

F32 F32_Sign(F32 f)
{
  if (f < 0)
    return -1;

  return 1;
}

F32 F32_Lerp(F32 a, F32 b, F32 t) { return a * (t - 1.0f) + b * t; }
S32 S32_Lerp(S32 a, S32 b, F32 t)
{
  return (S32)(a * (t - 1.0f)) + (S32)(b * t);
}

// NOTE(calco): -- Vector Conversion Functions --
Vec2S32 Vec2F32_ToVec2S32(Vec2F32 vec2f)
{
  return Vec2S32_Make((S32)(vec2f.x), (S32)(vec2f.y));
}

Vec3F32 Vec2F32_ToVec3F32(Vec2F32 vec2f)
{
  return Vec3F32_Make(vec2f.x, vec2f.y, 0.f);
}

Vec2F32 Vec2S32_ToVec2F32(Vec2S32 vec2s)
{
  return Vec2F32_Make((F32)(vec2s.x), (F32)(vec2s.y));
}

Vec3S32 Vec2S32_ToVec3S32(Vec2S32 vec2s)
{
  return Vec3S32_Make(vec2s.x, vec2s.y, 0);
}

Vec2F32 Vec3F32_ToVec2F32(Vec3F32 vec3f)
{
  return Vec2F32_Make(vec3f.x, vec3f.y);
}

Vec2S32 Vec3S32_ToVec2S32(Vec3S32 vec3s)
{
  return Vec2S32_Make(vec3s.x, vec3s.y);
}

// NOTE(calco): -- Vector2 Helper Functions --
Vec2F32 Vec2F32_Make(F32 a, F32 b)
{
  Vec2F32 v;
  v.x = a;
  v.y = b;
  return v;
}
Vec2F32 Vec2F32_Add(Vec2F32 a, Vec2F32 b)
{
  return Vec2F32_Make(a.x + b.x, a.y + b.y);
}

Vec2F32 Vec2F32_Sub(Vec2F32 a, Vec2F32 b)
{
  return Vec2F32_Make(a.x - b.x, a.y - b.y);
}

Vec2F32 Vec2F32_Mult(Vec2F32 a, Vec2F32 b)
{
  return Vec2F32_Make(a.x * b.x, a.y * b.y);
}

Vec2F32 Vec2F32_Div(Vec2F32 a, Vec2F32 b)
{
  return Vec2F32_Make(a.x / b.x, a.y / b.y);
}

Vec2F32 Vec2F32_AddScalar(Vec2F32 a, F32 b)
{
  return Vec2F32_Make(a.x + b, a.y + b);
}

Vec2F32 Vec2F32_SubScalar(Vec2F32 a, F32 b)
{
  return Vec2F32_Make(a.x - b, a.y - b);
}

Vec2F32 Vec2F32_DivScalar(Vec2F32 a, F32 b)
{
  return Vec2F32_Make(a.x / b, a.y / b);
}

Vec2F32 Vec2F32_MultScalar(Vec2F32 a, F32 b)
{
  return Vec2F32_Make(a.x * b, a.y * b);
}

F32 Vec2F32_Dot(Vec2F32 a, Vec2F32 b) { return a.x * b.x + a.y * b.y; }

F32 Vec2F32_Magnitude(Vec2F32 a)
{
  return F32_SquareRoot(a.x * a.x + a.y * a.y);
}

F32 Vec2F32_SqrMagnitude(Vec2F32 a) { return a.x * a.x + a.y * a.y; }

Vec2F32 Vec2F32_Normalize(Vec2F32 a)
{
  F32 mag = Vec2F32_Magnitude(a);

  if (F32_Abs(mag) < 0.0000001f)
    return Vec2F32_Zero;

  return Vec2F32_Make(a.x / mag, a.y / mag);
}

Vec2F32 Vec2F32_Lerp(Vec2F32 a, Vec2F32 b, F32 t)
{
  return Vec2F32_Make(F32_Lerp(a.x, b.x, t), F32_Lerp(a.y, b.y, t));
}

Vec2S32 Vec2S32_Make(S32 a, S32 b)
{
  Vec2S32 v;
  v.x = a;
  v.y = b;
  return v;
}

Vec2S32 Vec2S32_Add(Vec2S32 a, Vec2S32 b)
{
  return Vec2S32_Make(a.x + b.x, a.y + b.y);
}

Vec2S32 Vec2S32_Sub(Vec2S32 a, Vec2S32 b)
{
  return Vec2S32_Make(a.x - b.x, a.y - b.y);
}

Vec2S32 Vec2S32_Mult(Vec2S32 a, Vec2S32 b)
{
  return Vec2S32_Make(a.x * b.x, a.y * b.y);
}

Vec2S32 Vec2S32_Div(Vec2S32 a, Vec2S32 b)
{
  return Vec2S32_Make(a.x / b.x, a.y / b.y);
}

Vec2S32 Vec2S32_AddScalar(Vec2S32 a, S32 b)
{
  return Vec2S32_Make(a.x + b, a.y + b);
}

Vec2S32 Vec2S32_SubScalar(Vec2S32 a, S32 b)
{
  return Vec2S32_Make(a.x - b, a.y - b);
}

Vec2S32 Vec2S32_DivScalar(Vec2S32 a, S32 b)
{
  return Vec2S32_Make(a.x / b, a.y / b);
}

Vec2S32 Vec2S32_MultScalar(Vec2S32 a, S32 b)
{
  return Vec2S32_Make(a.x * b, a.y * b);
}

F32 Vec2S32_Dot(Vec2S32 a, Vec2S32 b) { return a.x * b.x + a.y * b.y; }

F32 Vec2S32_Magnitude(Vec2S32 a)
{
  return F32_SquareRoot(a.x * a.x + a.y * a.y);
}

F32 Vec2S32_SqrMagnitude(Vec2S32 a) { return a.x * a.x + a.y * a.y; }

Vec2S32 Vec2S32_Normalize(Vec2S32 a)
{
  F32 mag = Vec2S32_Magnitude(a);
  return Vec2S32_Make((S32)(a.x / mag), (S32)(a.y / mag));
}

Vec2S32 Vec2S32_Lerp(Vec2S32 a, Vec2S32 b, F32 t)
{
  return Vec2S32_Make(S32_Lerp(a.x, b.x, t), S32_Lerp(a.y, b.y, t));
}

// NOTE(calco): -- Vector3 Helper Functions --
Vec3F32 Vec3F32_Make(F32 a, F32 b, F32 c)
{
  Vec3F32 v;
  v.x = a;
  v.y = b;
  v.z = c;
  return v;
}

Vec3F32 Vec3F32_Add(Vec3F32 a, Vec3F32 b)
{
  return Vec3F32_Make(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3F32 Vec3F32_Sub(Vec3F32 a, Vec3F32 b)
{
  return Vec3F32_Make(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3F32 Vec3F32_Mult(Vec3F32 a, Vec3F32 b)
{
  return Vec3F32_Make(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3F32 Vec3F32_Div(Vec3F32 a, Vec3F32 b)
{
  return Vec3F32_Make(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3F32 Vec3F32_AddScalar(Vec3F32 a, F32 b)
{
  return Vec3F32_Make(a.x + b, a.y + b, a.z + b);
}

Vec3F32 Vec3F32_SubScalar(Vec3F32 a, F32 b)
{
  return Vec3F32_Make(a.x - b, a.y - b, a.z - b);
}

Vec3F32 Vec3F32_DivScalar(Vec3F32 a, F32 b)
{
  return Vec3F32_Make(a.x / b, a.y / b, a.z / b);
}

Vec3F32 Vec3F32_MultScalar(Vec3F32 a, F32 b)
{
  return Vec3F32_Make(a.x * b, a.y * b, a.z * b);
}

F32 Vec3F32_Dot(Vec3F32 a, Vec3F32 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3F32 Vec3F32_Cross(Vec3F32 a, Vec3F32 b)
{
  Vec3F32 c = {0};
  c.x       = (a.y * b.z) - (a.z * b.y);
  c.y       = (a.z * b.x) - (a.x * b.z);
  c.z       = (a.x * b.y) - (a.y * b.x);
  return c;
}

F32 Vec3F32_Magnitude(Vec3F32 a)
{
  return F32_SquareRoot(a.x * a.x + a.y * a.y + a.z * a.z);
}

F32 Vec3F32_SqrMagnitude(Vec3F32 a)
{
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

Vec3F32 Vec3F32_Normalize(Vec3F32 a)
{
  F32 mag = Vec3F32_Magnitude(a);
  if (F32_Abs(mag) < 0.00001f)
    return Vec3F32_Zero;
  return Vec3F32_Make(a.x / mag, a.y / mag, a.z / mag);
}

Vec3F32 Vec3F32_Lerp(Vec3F32 a, Vec3F32 b, F32 t)
{
  return Vec3F32_Make(
      F32_Lerp(a.x, b.x, t), F32_Lerp(a.y, b.y, t), F32_Lerp(a.z, b.z, t)
  );
}

Vec3F32 Vec3F32_RotateAxis(Vec3F32 vec, Vec3F32 axis, F32 radians)
{
  F32 half_angle     = radians * 0.5f;
  F32 sin_half_angle = F32_Sin(half_angle);

  QuatF32 r = {0};
  r.x       = axis.x * sin_half_angle;
  r.y       = axis.y * sin_half_angle;
  r.z       = axis.z * sin_half_angle;
  r.w       = F32_Cos(half_angle);

  r                   = QuatF32_Normalize(r);
  QuatF32 r_conjugate = QuatF32_Conjugate(r);
  QuatF32 v           = QuatF32_Make(vec.x, vec.y, vec.z, 0.f);
  QuatF32 w           = QuatF32_Mult(QuatF32_Mult(r, v), r_conjugate);

  return Vec3F32_Make(w.x, w.y, w.z);
}

Vec3S32 Vec3S32_Make(S32 a, S32 b, S32 c)
{
  Vec3S32 v;
  v.x = a;
  v.y = b;
  v.z = c;
  return v;
}

Vec3S32 Vec3S32_Add(Vec3S32 a, Vec3S32 b)
{
  return Vec3S32_Make(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3S32 Vec3S32_Sub(Vec3S32 a, Vec3S32 b)
{
  return Vec3S32_Make(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3S32 Vec3S32_Mult(Vec3S32 a, Vec3S32 b)
{
  return Vec3S32_Make(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3S32 Vec3S32_Div(Vec3S32 a, Vec3S32 b)
{
  return Vec3S32_Make(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3S32 Vec3S32_AddScalar(Vec3S32 a, S32 b)
{
  return Vec3S32_Make(a.x + b, a.y + b, a.z + b);
}

Vec3S32 Vec3S32_SubScalar(Vec3S32 a, S32 b)
{
  return Vec3S32_Make(a.x - b, a.y - b, a.z - b);
}

Vec3S32 Vec3S32_DivScalar(Vec3S32 a, S32 b)
{
  return Vec3S32_Make(a.x / b, a.y / b, a.z / b);
}

Vec3S32 Vec3S32_MultScalar(Vec3S32 a, S32 b)
{
  return Vec3S32_Make(a.x * b, a.y * b, a.z * b);
}

F32 Vec3S32_Dot(Vec3S32 a, Vec3S32 b)
{
  return (F32)(a.x * b.x + a.y * b.y + a.z * b.z);
}

Vec3F32 Vec3S32_Cross(Vec3S32 a, Vec3S32 b)
{
  Vec3F32 c = {0};
  c.x       = (F32)((a.y * b.z) - (a.z * b.y));
  c.y       = (F32)((a.z * b.x) - (a.x * b.z));
  c.z       = (F32)((a.x * b.y) - (a.y * b.x));
  return c;
}

F32 Vec3S32_Magnitude(Vec3S32 a)
{
  return F32_SquareRoot(a.x * a.x + a.y * a.y + a.z * a.z);
}

F32 Vec3S32_SqrMagnitude(Vec3S32 a)
{
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

Vec3S32 Vec3S32_Normalize(Vec3S32 a)
{
  F32 mag = Vec3S32_Magnitude(a);
  return Vec3S32_Make((S32)(a.x / mag), (S32)(a.y / mag), (S32)(a.z / mag));
}

Vec3S32 Vec3S32_Lerp(Vec3S32 a, Vec3S32 b, F32 t)
{
  return Vec3S32_Make(
      S32_Lerp(a.x, b.x, t), S32_Lerp(a.y, b.y, t), S32_Lerp(a.z, b.z, t)
  );
}

// NOTE(calco): -- Rect Helper Functions --
RectF32 RectF32_Make(F32 x, F32 y, F32 w, F32 h)
{
  RectF32 r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  return r;
}

B8 RectF32_ContainsPoint(RectF32 rect, Vec2F32 point)
{
  return rect.x <= point.x && rect.y <= point.y && rect.x + rect.w >= point.x &&
         rect.y + rect.h >= point.y;
}

B8 RectF32_Overlaps(RectF32 a, RectF32 b)
{
  B8 x = (a.x >= b.x && a.x <= b.x + b.w) ||
         (a.x + a.w >= b.x && a.x + a.w <= b.x + b.w) ||
         (a.x <= b.x && a.x + a.w >= b.x + b.w);
  B8 y = (a.y >= b.y && a.y <= b.y + b.h) ||
         (a.y + a.h >= b.y && a.y + a.h <= b.y + b.h) ||
         (a.y <= b.y && a.y + a.h >= b.y + b.h);

  return x && y;
}

B8 RectF32_ContainsRect(RectF32 a, RectF32 b)
{
  RectF32 tmp = a;
  a           = b;
  b           = tmp;

  B8 x = (a.x >= b.x && a.x <= b.x + b.w) &&
         (a.x + a.w >= b.x && a.x + a.w <= b.x + b.w);
  B8 y = (a.y >= b.y && a.y <= b.y + b.h) &&
         (a.y + a.h >= b.y && a.y + a.h <= b.y + b.h);

  return x && y;
}

RectF32 RectF32_GetOverlap(RectF32 a, RectF32 b)
{
  Vec2F32 min = Vec2F32_Make(Max(a.x, b.x), Max(a.y, b.y));
  Vec2F32 max = Vec2F32_Make((a.x + a.w, b.x + b.w), Min(a.y + a.h, b.y + b.h));

  return RectF32_Make(min.x, min.y, max.x - min.x, max.y - min.y);
}

RectF32 RectF32_CullUV(RectF32 quad, RectF32 uv, RectF32 cull_quad)
{
  if (!RectF32_Overlaps(quad, cull_quad) ||
      RectF32_ContainsRect(cull_quad, quad))
  {
    return uv;
  }

  B8 x_shift_constant =
      !(quad.x >= cull_quad.x && quad.x <= cull_quad.x + cull_quad.w);
  B8 y_shift_constant =
      !(quad.y >= cull_quad.y && quad.y <= cull_quad.y + cull_quad.h);

  F32 uv_xratio   = uv.w / quad.w;
  F32 uv_yratio   = uv.h / quad.h;
  RectF32 overlap = RectF32_GetOverlap(quad, cull_quad);
  F32 culled_x    = uv.x + (quad.w - overlap.w) * uv_xratio * x_shift_constant;
  F32 culled_y    = uv.y + (quad.h - overlap.h) * uv_yratio * y_shift_constant;
  F32 culled_w    = overlap.w * uv_xratio;
  F32 culled_h    = overlap.h * uv_yratio;
  return RectF32_Make(culled_x, culled_y, culled_w, culled_h);
}

// NOTE(calco): -- Matrix Helper Functions --
Mat3x3F32 Mat3x3_Identity() { return Mat3x3_MakeValue(1.0f); }

Mat3x3F32 Mat3x3_MakeValue(F32 value)
{
  Mat3x3F32 mat = {{
      {value, 0.0f, 0.0f},
      {0.0f, value, 0.0f},
      {0.0f, 0.0f, value},
  }};

  return mat;
}

Mat3x3F32 Mat3x3_MakeTransform(Vec2F32 translate)
{
  Mat3x3F32 mat      = Mat3x3_MakeValue(1.0f);
  mat.elements[0][2] = translate.x;
  mat.elements[1][2] = translate.y;
  return mat;
}

Mat3x3F32 Mat3x3_MakeScale(Vec2F32 scale)
{
  Mat3x3F32 mat      = Mat3x3_MakeValue(1.0f);
  mat.elements[0][0] = scale.x;
  mat.elements[1][1] = scale.y;
  return mat;
}

Mat3x3F32 Mat3x3_MakeRotation(F32 radians)
{
  Mat3x3F32 mat      = Mat3x3_MakeValue(1.0f);
  mat.elements[0][0] = +F32_Cos(radians);
  mat.elements[0][1] = -F32_Sin(radians);
  mat.elements[1][0] = +F32_Sin(radians);
  mat.elements[1][1] = +F32_Cos(radians);
  return mat;
}

Mat3x3F32 Mat3x3_Mult(Mat3x3F32 a, Mat3x3F32 b)
{
  Mat3x3F32 mat = {0};
  for (U64 y = 0; y < 3; ++y)
    for (U64 x = 0; x < 3; ++x)
      mat.elements[y][x] =
          (a.elements[y][0] * b.elements[0][x] +
           a.elements[y][1] * b.elements[1][x] +
           a.elements[y][2] * b.elements[2][x]);
  return mat;
}

Mat3x3F32 Mat3x3_Scale(Mat3x3F32 a, F32 scale)
{
  Mat3x3F32 mat = {0};
  for (U64 y = 0; y < 3; ++y)
    for (U64 x = 0; x < 3; ++x)
      mat.elements[y][x] = mat.elements[y][x] * scale;

  return mat;
}

Mat3x3F32 Mat3x3_Transpose(Mat3x3F32 mat)
{
  Mat3x3F32 m = {0};
  for (U64 y = 0; y < 3; ++y)
    for (U64 x = 0; x < 3; ++x)
      m.elements[y][x] = mat.elements[x][y];

  return m;
}

// Matrix4x4
Mat4x4F32 Mat4x4_Identity() { return Mat4x4_MakeValue(1.0f); }

Mat4x4F32 Mat4x4_MakeValue(F32 value)
{
  Mat4x4F32 mat = {{
      {value, 0.0f, 0.0f, 0.0f},
      {0.0f, value, 0.0f, 0.0f},
      {0.0f, 0.0f, value, 0.0f},
      {0.0f, 0.0f, 0.0f, value},
  }};

  return mat;
}

Mat4x4F32 Mat4x4_MakeTranslate(Vec3F32 translate)
{
  Mat4x4F32 mat      = Mat4x4_MakeValue(1.0f);
  mat.elements[0][3] = translate.x;
  mat.elements[1][3] = translate.y;
  mat.elements[2][3] = translate.z;
  return mat;
}

Mat4x4F32 Mat4x4_MakeScale(Vec3F32 scale)
{
  Mat4x4F32 mat      = Mat4x4_MakeValue(1.0f);
  mat.elements[0][0] = scale.x;
  mat.elements[1][1] = scale.y;
  mat.elements[2][2] = scale.z;
  return mat;
}

Mat4x4F32 Mat4x4_MakeRotation(Vec3F32 axis, F32 radians)
{
  Mat4x4F32 mat      = Mat4x4_MakeValue(1.f);
  axis               = Vec3F32_Normalize(axis);
  F32 sin_theta      = F32_Sin(radians);
  F32 cos_theta      = F32_Cos(radians);
  F32 cos_value      = 1.f - cos_theta;
  mat.elements[0][0] = (axis.x * axis.x * cos_value) + cos_theta;
  mat.elements[1][0] = (axis.x * axis.y * cos_value) + (axis.z * sin_theta);
  mat.elements[2][0] = (axis.x * axis.z * cos_value) - (axis.y * sin_theta);
  mat.elements[0][1] = (axis.y * axis.x * cos_value) - (axis.z * sin_theta);
  mat.elements[1][1] = (axis.y * axis.y * cos_value) + cos_theta;
  mat.elements[2][1] = (axis.y * axis.z * cos_value) + (axis.x * sin_theta);
  mat.elements[0][2] = (axis.z * axis.x * cos_value) + (axis.y * sin_theta);
  mat.elements[1][2] = (axis.z * axis.y * cos_value) - (axis.x * sin_theta);
  mat.elements[2][2] = (axis.z * axis.z * cos_value) + cos_theta;
  return mat;
}

Mat4x4F32 Mat4x4_MakeLookAt(Vec3F32 pos, Vec3F32 target, Vec3F32 up)
{
  Vec3F32 Z = Vec3F32_Normalize(Vec3F32_Sub(pos, target));
  Vec3F32 Y = up;
  Vec3F32 X = Vec3F32_Cross(Y, Z);
  Y         = Vec3F32_Cross(Z, X);

  X = Vec3F32_Normalize(X);
  Y = Vec3F32_Normalize(Y);

  Mat4x4F32 viewMatrix;

  viewMatrix.elements[0][0] = X.x;
  viewMatrix.elements[1][0] = X.y;
  viewMatrix.elements[2][0] = X.z;
  viewMatrix.elements[3][0] = -Vec3F32_Dot(X, pos);
  viewMatrix.elements[0][1] = Y.x;
  viewMatrix.elements[1][1] = Y.y;
  viewMatrix.elements[2][1] = Y.z;
  viewMatrix.elements[3][1] = -Vec3F32_Dot(Y, pos);
  viewMatrix.elements[0][2] = Z.x;
  viewMatrix.elements[1][2] = Z.y;
  viewMatrix.elements[2][2] = Z.z;
  viewMatrix.elements[3][2] = -Vec3F32_Dot(Z, pos);
  viewMatrix.elements[0][3] = 0;
  viewMatrix.elements[1][3] = 0;
  viewMatrix.elements[2][3] = 0;
  viewMatrix.elements[3][3] = 1.0f;

  return viewMatrix;
}

Mat4x4F32 Mat4x4_MakeOrthographic(
    F32 left, F32 right, F32 bottom, F32 top, F32 c_near, F32 c_far
)
{
  Mat4x4F32 ortho_matrix = Mat4x4_MakeValue(0.f);

  ortho_matrix.elements[0][0] = 2.f / (right - left);
  ortho_matrix.elements[1][1] = 2.f / (top - bottom);
  ortho_matrix.elements[2][2] = -2.f / (c_far - c_near);
  ortho_matrix.elements[3][3] = 1.f;

  ortho_matrix.elements[3][0] = -(right + left) / (right - left);
  ortho_matrix.elements[3][1] = -(top + bottom) / (top - bottom);
  ortho_matrix.elements[3][2] = -(c_far + c_near) / (c_far - c_near);

  return ortho_matrix;
}

Mat4x4F32
Mat4x4_MakePerspective(F32 fov, F32 aspect_ratio, F32 c_near, F32 c_far)
{
  Mat4x4F32 projection_matrix = Mat4x4_MakeValue(1.f);

  F32 half_fov     = F32_DegToRad(fov * 0.5f);
  F32 half_fov_tan = F32_Tan(half_fov);

  projection_matrix.elements[0][0] = 1.f / (half_fov_tan * aspect_ratio);
  projection_matrix.elements[1][1] = 1.f / (half_fov_tan);
  projection_matrix.elements[2][2] = -(c_far + c_near) / (c_far - c_near);
  projection_matrix.elements[3][3] = 0.f;

  projection_matrix.elements[2][3] = -1.f;
  projection_matrix.elements[3][2] = -(2.f * c_far * c_near) / (c_far - c_near);

  return projection_matrix;
}

// TODO(calco): Add some functions to create a 4x4 ortographic / perspective

Mat4x4F32 Mat4x4_Mult(Mat4x4F32 a, Mat4x4F32 b)
{
  Mat4x4F32 mat = {0};
  for (U64 y = 0; y < 4; ++y)
    for (U64 x = 0; x < 4; ++x)
      mat.elements[y][x] =
          (a.elements[y][0] * b.elements[0][x] +
           a.elements[y][1] * b.elements[1][x] +
           a.elements[y][2] * b.elements[2][x] +
           a.elements[y][3] * b.elements[3][x]);

  return mat;
}

Mat4x4F32 Mat4x4_Scale(Mat4x4F32 a, F32 scale)
{
  Mat4x4F32 mat = {0};
  for (U64 y = 0; y < 4; ++y)
    for (U64 x = 0; x < 4; ++x)
      mat.elements[y][x] = mat.elements[y][x] * scale;

  return mat;
}

Mat4x4F32 Mat4x4_Transpose(Mat4x4F32 mat)
{
  Mat4x4F32 m = {0};
  for (U64 y = 0; y < 4; ++y)
    for (U64 x = 0; x < 4; ++x)
      m.elements[y][x] = mat.elements[x][y];

  return m;
}

// NOTE(calco): -- Matrix Vector Math --
Vec2F32 Vec2F32_ApplyMatrix(Mat3x3F32 mat, Vec2F32 vec)
{
  Vec2F32 res = {0};

  res.x = mat.elements[0][0] * vec.x + mat.elements[0][1] * vec.y +
          mat.elements[0][2];
  res.y = mat.elements[1][0] * vec.x + mat.elements[1][1] * vec.y +
          mat.elements[1][2];

  return res;
}

Vec3F32 Vec3F32_ApplyMatrix(Mat4x4F32 mat, Vec3F32 vec)
{
  Vec3F32 res = {0};

  res.x = mat.elements[0][0] * vec.x + mat.elements[0][1] * vec.y +
          mat.elements[0][2] * vec.z + mat.elements[0][3];
  res.y = mat.elements[1][0] * vec.x + mat.elements[1][1] * vec.y +
          mat.elements[1][2] * vec.z + mat.elements[1][3];
  res.z = mat.elements[2][0] * vec.x + mat.elements[2][1] * vec.y +
          mat.elements[2][2] * vec.z + mat.elements[2][3];

  return res;
}

// NOTE(calco): -- Quaternion Helper Functions --
QuatF32 QuatF32_Identity() { return QuatF32_Make(0.f, 0.f, 0.f, 1.f); }

QuatF32 QuatF32_Make(F32 x, F32 y, F32 z, F32 w)
{
  QuatF32 quat = {0};
  quat.x       = x;
  quat.y       = y;
  quat.z       = z;
  quat.w       = w;
  return quat;
}

QuatF32 QuatF32_MakeFromAxisAngle(Vec3F32 axis, F32 radians)
{
  Vec3F32 axis_norm = Vec3F32_Normalize(axis);

  F32 half_theta = radians * 0.5f;

  Vec3F32 vec  = Vec3F32_MultScalar(axis_norm, F32_Sin(half_theta));
  QuatF32 quat = {0};
  quat.x       = vec.x;
  quat.y       = vec.y;
  quat.z       = vec.z;
  quat.w       = F32_Cos(half_theta);
  return quat;
}

QuatF32 QuatF32_MakeFromEulerAngles(F32 x, F32 y, F32 z)
{
  x = F32_DegToRad(x);
  y = F32_DegToRad(y);
  z = F32_DegToRad(z);

  F32 sinX = F32_Sin(x);
  F32 cosX = F32_Cos(x);
  F32 sinY = F32_Sin(y);
  F32 cosY = F32_Cos(y);
  F32 sinZ = F32_Sin(z);
  F32 cosZ = F32_Cos(z);

  QuatF32 q = {0};
  q.x       = sinX * cosY * cosZ - cosX * sinY * sinZ;
  q.y       = cosX * sinY * cosZ + sinX * cosY * sinZ;
  q.z       = cosX * cosY * sinZ - sinX * sinY * cosZ;
  q.w       = cosX * cosY * cosZ + sinX * sinY * sinZ;

  return q;
}

QuatF32 QuatF32_Add(QuatF32 a, QuatF32 b)
{
  QuatF32 q = {0};
  q.x       = a.x + b.x;
  q.y       = a.y + b.y;
  q.z       = a.z + b.z;
  q.w       = a.w + b.w;
  return q;
}

QuatF32 QuatF32_Sub(QuatF32 a, QuatF32 b)
{
  QuatF32 q = {0};
  q.x       = a.x - b.x;
  q.y       = a.y - b.y;
  q.z       = a.z - b.z;
  q.w       = a.w - b.w;
  return q;
}

QuatF32 QuatF32_Mult(QuatF32 a, QuatF32 b)
{
  QuatF32 q = {0};
  q.x       = (a.w * b.x) + (a.x * b.w) + (a.y * b.z) - (a.z * b.y);
  q.y       = (a.w * b.y) - (a.x * b.z) + (a.y * b.w) + (a.z * b.x);
  q.z       = (a.w * b.z) + (a.x * b.y) - (a.y * b.x) + (a.z * b.w);
  q.w       = (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z);
  return q;
}

QuatF32 QuatF32_MultScalar(QuatF32 a, F32 f)
{
  QuatF32 q = {0};
  q.x       = a.x * f;
  q.y       = a.y * f;
  q.z       = a.z * f;
  q.w       = a.w * f;
  return q;
}

QuatF32 QuatF32_Normalize(QuatF32 quat)
{
  F32 length = F32_SquareRoot(
      quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w
  );
  return QuatF32_MultScalar(quat, length);
}

F32 QuatF32_Dot(QuatF32 a, QuatF32 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

QuatF32 QuatF32_Lerp(QuatF32 a, QuatF32 b, F32 t)
{
  QuatF32 q = {0};
  q.x       = F32_Lerp(a.x, b.x, t);
  q.y       = F32_Lerp(a.y, b.y, t);
  q.z       = F32_Lerp(a.z, b.z, t);
  q.w       = F32_Lerp(a.w, b.w, t);
  return q;
}

QuatF32 QuatF32_Conjugate(QuatF32 quat)
{
  QuatF32 q = {0};
  q.w       = quat.w;
  q.x       = -quat.x;
  q.y       = -quat.y;
  q.z       = -quat.z;
  return q;
}

Mat4x4F32 QuatF32_Mat4x4FromQuatF32(QuatF32 quat)
{
  QuatF32 q_norm = QuatF32_Normalize(quat);
  F32 xx         = q_norm.x * q_norm.x;
  F32 yy         = q_norm.y * q_norm.y;
  F32 zz         = q_norm.z * q_norm.z;
  F32 xy         = q_norm.x * q_norm.y;
  F32 xz         = q_norm.x * q_norm.z;
  F32 yz         = q_norm.y * q_norm.z;
  F32 wx         = q_norm.w * q_norm.x;
  F32 wy         = q_norm.w * q_norm.y;
  F32 wz         = q_norm.w * q_norm.z;

  Mat4x4F32 result      = {0};
  result.elements[0][0] = 1.f - 2.f * (yy + zz);
  result.elements[0][1] = 2.f * (xy + wz);
  result.elements[0][2] = 2.f * (xz - wy);
  result.elements[0][3] = 0.f;
  result.elements[1][0] = 2.f * (xy - wz);
  result.elements[1][1] = 1.f - 2.f * (xx + zz);
  result.elements[1][2] = 2.f * (yz + wx);
  result.elements[1][3] = 0.f;
  result.elements[2][0] = 2.f * (xz + wy);
  result.elements[2][1] = 2.f * (yz - wx);
  result.elements[2][2] = 1.f - 2.f * (xx + yy);
  result.elements[2][3] = 0.f;
  result.elements[3][0] = 0.f;
  result.elements[3][1] = 0.f;
  result.elements[3][2] = 0.f;
  result.elements[3][3] = 1.f;
  return result;
}

Vec3F32 QuatF32_RotateVector(QuatF32 quat, Vec3F32 vec)
{
  QuatF32 v_quat = QuatF32_Make(vec.x, vec.y, vec.z, 0.0f);
  QuatF32 result_quat =
      QuatF32_Mult(QuatF32_Mult(quat, v_quat), QuatF32_Conjugate(quat));
  Vec3F32 rotated_vector =
      Vec3F32_Make(result_quat.x, result_quat.y, result_quat.z);

  return rotated_vector;
}