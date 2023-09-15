#include "base_math.h"

// NOTE(calco): -- Base Math --
F32 F32_Abs(F32 f)
{
  if (f < 0)
    return -f;

  return f;
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
  return Vec3F32_Make(a.x / mag, a.y / mag, a.z / mag);
}

Vec3F32 Vec3F32_Lerp(Vec3F32 a, Vec3F32 b, F32 t)
{
  return Vec3F32_Make(
      F32_Lerp(a.x, b.x, t), F32_Lerp(a.y, b.y, t), F32_Lerp(a.z, b.z, t)
  );
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