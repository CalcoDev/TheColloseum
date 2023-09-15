#include "base_math.h"

// NOTE(calco): -- Base Math --
S32 S32_Lerp(S32 a, S32 b, F32 t)
{
  return (S32)(a * (t - 1.0f)) + (S32)(b * t);
}
F32 F32_Lerp(F32 a, F32 b, F32 t) { return a * (t - 1.0f) + b * t; }

// NOTE(calco): -- Vector2 Helper Functions --
Vec2F32 V2F32(F32 a, F32 b)
{
  Vec2F32 v;
  v.x = a;
  v.y = b;
  return v;
}
Vec2F32 V2F32_Add(Vec2F32 a, Vec2F32 b) { return V2F32(a.x + b.x, a.y + b.y); }
Vec2F32 V2F32_Sub(Vec2F32 a, Vec2F32 b) { return V2F32(a.x - b.x, a.y - b.y); }
Vec2F32 V2F32_Mult(Vec2F32 a, Vec2F32 b) { return V2F32(a.x * b.x, a.y * b.y); }
Vec2F32 V2F32_Div(Vec2F32 a, Vec2F32 b) { return V2F32(a.x / b.x, a.y / b.y); }
Vec2F32 V2F32_Scale(Vec2F32 a, F32 b) { return V2F32(a.x * b, a.y * b); }
F32 V2F32_Dot(Vec2F32 a, Vec2F32 b) { return a.x * b.x + a.y * b.y; }
F32 V2F32_Magnitude(Vec2F32 a) { return SquareRootF32(a.x * a.x + a.y * a.y); }
F32 V2F32_SqrMagnitude(Vec2F32 a) { return a.x * a.x + a.y * a.y; }
Vec2F32 V2F32_Normalize(Vec2F32 a)
{
  F32 mag = V2F32_Magnitude(a);
  return V2F32(a.x / mag, a.y / mag);
}
Vec2F32 V2F32_Lerp(Vec2F32 a, Vec2F32 b, F32 t)
{
  return V2F32(F32_Lerp(a.x, b.x, t), F32_Lerp(a.y, b.y, t));
}

Vec2S32 V2S32(S32 a, S32 b)
{
  Vec2S32 v;
  v.x = a;
  v.y = b;
  return v;
}
Vec2S32 V2S32_Add(Vec2S32 a, Vec2S32 b) { return V2S32(a.x + b.x, a.y + b.y); }
Vec2S32 V2S32_Sub(Vec2S32 a, Vec2S32 b) { return V2S32(a.x - b.x, a.y - b.y); }
Vec2S32 V2S32_Mult(Vec2S32 a, Vec2S32 b) { return V2S32(a.x * b.x, a.y * b.y); }
Vec2S32 V2S32_Div(Vec2S32 a, Vec2S32 b) { return V2S32(a.x / b.x, a.y / b.y); }
Vec2S32 V2S32_Scale(Vec2S32 a, S32 b) { return V2S32(a.x * b, a.y * b); }
F32 V2S32_Dot(Vec2S32 a, Vec2S32 b) { return a.x * b.x + a.y * b.y; }
F32 V2S32_Magnitude(Vec2S32 a) { return SquareRootF32(a.x * a.x + a.y * a.y); }
F32 V2S32_SqrMagnitude(Vec2S32 a) { return a.x * a.x + a.y * a.y; }
Vec2S32 V2S32_Normalize(Vec2S32 a)
{
  F32 mag = V2S32_Magnitude(a);
  return V2S32((S32)(a.x / mag), (S32)(a.y / mag));
}
Vec2S32 V2S32_Lerp(Vec2S32 a, Vec2S32 b, F32 t)
{
  return V2S32(S32_Lerp(a.x, b.x, t), S32_Lerp(a.y, b.y, t));
}

// NOTE(calco): -- Vector3 Helper Functions --
Vec3F32 V3F32(F32 a, F32 b, F32 c)
{
  Vec3F32 v;
  v.x = a;
  v.y = b;
  v.z = c;
  return v;
}
Vec3F32 V3F32_Add(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3F32 V3F32_Sub(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3F32 V3F32_Mult(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x * b.x, a.y * b.y, a.z * b.z);
}
Vec3F32 V3F32_Div(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x / b.x, a.y / b.y, a.z / b.z);
}
Vec3F32 V3F32_Scale(Vec3F32 a, F32 b)
{
  return V3F32(a.x * b, a.y * b, a.z * b);
}
F32 V3F32_Dot(Vec3F32 a, Vec3F32 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
F32 V3F32_Magnitude(Vec3F32 a)
{
  return SquareRootF32(a.x * a.x + a.y * a.y + a.z * a.z);
}
F32 V3F32_SqrMagnitude(Vec3F32 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
Vec3F32 V3F32_Normalize(Vec3F32 a)
{
  F32 mag = V3F32_Magnitude(a);
  return V3F32(a.x / mag, a.y / mag, a.z / mag);
}
Vec3F32 V3F32_Lerp(Vec3F32 a, Vec3F32 b, F32 t)
{
  return V3F32(
      F32_Lerp(a.x, b.x, t), F32_Lerp(a.y, b.y, t), F32_Lerp(a.z, b.z, t)
  );
}

Vec3S32 V3S32(S32 a, S32 b, S32 c)
{
  Vec3S32 v;
  v.x = a;
  v.y = b;
  v.z = c;
  return v;
}
Vec3S32 V3S32_Add(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3S32 V3S32_Sub(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3S32 V3S32_Mult(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x * b.x, a.y * b.y, a.z * b.z);
}
Vec3S32 V3S32_Div(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x / b.x, a.y / b.y, a.z / b.z);
}
Vec3S32 V3S32_Scale(Vec3S32 a, S32 b)
{
  return V3S32(a.x * b, a.y * b, a.z * b);
}
F32 V3S32_Dot(Vec3S32 a, Vec3S32 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
F32 V3S32_Magnitude(Vec3S32 a)
{
  return SquareRootF32(a.x * a.x + a.y * a.y + a.z * a.z);
}
F32 V3S32_SqrMagnitude(Vec3S32 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
Vec3S32 V3S32_Normalize(Vec3S32 a)
{
  F32 mag = V3S32_Magnitude(a);
  return V3S32((S32)(a.x / mag), (S32)(a.y / mag), (S32)(a.z / mag));
}
Vec3S32 V3S32_Lerp(Vec3S32 a, Vec3S32 b, F32 t)
{
  return V3S32(
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
  mat.elements[0][0] = +CosF32(radians);
  mat.elements[0][1] = -SinF32(radians);
  mat.elements[1][0] = +SinF32(radians);
  mat.elements[1][1] = +CosF32(radians);
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

Mat4x4F32 Mat4x4_MakeTransform(Vec3F32 translate)
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
  axis               = V3F32_Normalize(axis);
  F32 sin_theta      = SinF32(radians);
  F32 cos_theta      = CosF32(radians);
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