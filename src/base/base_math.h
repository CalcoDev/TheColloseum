#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "base_types.h"
#include <math.h>

// NOTE(calco): -- Constants --
static F32 F32_Infinity = INFINITY;

static F32 F32_Pi             = 3.1415926535897f;
static F32 F32_EulersConstant = 2.7182818284590452353602874713527f;

static F64 F64_Pi             = 3.1415926535897;
static F64 F64_EulersConstant = 2.7182818284590452353602874713527;

// NOTE(calco): -- Base Math --
#define F32_Floor(f)      floorf(f);
#define F32_Ceil(f)       ceilf(f);
#define F32_Round(f)      roundf(f);
#define F32_DegToRad(deg) ((F32_Pi / 180.f) * (deg))
#define F32_RadToDeg(rad) ((180.f / F32_Pi) * (rad))
#define F32_SquareRoot(f) sqrtf(f);
#define F32_Sin(f)        sinf(f);
#define F32_Cos(f)        cosf(f);
#define F32_Tan(f)        tanf(f);

F32 F32_Abs(F32 f);

F32 F32_Lerp(F32 a, F32 b, F32 t);
S32 S32_Lerp(S32 a, S32 b, F32 t);

// NOTE(calco): -- Vector2 Types --
typedef struct Vec2F32
{
  F32 x;
  F32 y;
} Vec2F32;

typedef struct Vec2S32
{
  S32 x;
  S32 y;
} Vec2S32;

// NOTE(calco): -- Vector3 Types --
typedef struct Vec3F32
{
  F32 x;
  F32 y;
  F32 z;
} Vec3F32;

typedef struct Vec3S32
{
  S32 x;
  S32 y;
  S32 z;
} Vec3S32;

// NOTE(calco): -- Vector Conversion Functions --
Vec2S32 Vec2F32_ToVec2S32(Vec2F32 vec2f);
Vec3F32 Vec2F32_ToVec3F32(Vec2F32 vec2f);

Vec2F32 Vec2S32_ToVec2F32(Vec2S32 vec2s);
Vec3S32 Vec2S32_ToVec3S32(Vec2S32 vec2s);

Vec2F32 Vec3F32_ToVec2F32(Vec3F32 vec3f);
Vec2S32 Vec3S32_ToVec2S32(Vec3S32 vec3s);

// NOTE(calco): -- Matrix Types --

/**
 * @brief A row-major 3x3 matrix representation.
 * @warning All default Mat3x3_ functions require row-major order matrices to
 * function properly!
 */
typedef struct Mat3x3F32
{
  F32 elements[3][3];
} Mat3x3F32;

/**
 * @brief A row-major 4x4 matrix representation.
 * @warning All default Mat4x4_ functions require row-major order matrices to
 * function properly!
 */
typedef struct Mat4x4F32
{
  F32 elements[4][4];
} Mat4x4F32;

// NOTE(calco): -- Quaternions --
typedef struct QuatF32
{
  F32 x;
  F32 y;
  F32 z;
  F32 w;
} QuatF32;

// NOTE(calco): -- Vector2 Helper Functions --
// yes yes, wrong naming convention, should be Vec2F32Add(), but for usability
// and readabilitys sake it will be AddVec2F32_Make();

Vec2F32 Vec2F32_Make(F32 a, F32 b);
Vec2F32 Vec2F32_Add(Vec2F32 a, Vec2F32 b);
Vec2F32 Vec2F32_Sub(Vec2F32 a, Vec2F32 b);
Vec2F32 Vec2F32_Mult(Vec2F32 a, Vec2F32 b);
Vec2F32 Vec2F32_Div(Vec2F32 a, Vec2F32 b);
Vec2F32 Vec2F32_AddScalar(Vec2F32 a, F32 b);
Vec2F32 Vec2F32_SubScalar(Vec2F32 a, F32 b);
Vec2F32 Vec2F32_DivScalar(Vec2F32 a, F32 b);
Vec2F32 Vec2F32_MultScalar(Vec2F32 a, F32 b);
F32 Vec2F32_Dot(Vec2F32 a, Vec2F32 b);
F32 Vec2F32_Magnitude(Vec2F32 a);
F32 Vec2F32_SqrMagnitude(Vec2F32 a);
Vec2F32 Vec2F32_Normalize(Vec2F32 a);
Vec2F32 Vec2F32_Lerp(Vec2F32 a, Vec2F32 b, F32 t);

Vec2S32 Vec2S32_Make(S32 a, S32 b);
Vec2S32 Vec2S32_Add(Vec2S32 a, Vec2S32 b);
Vec2S32 Vec2S32_Sub(Vec2S32 a, Vec2S32 b);
Vec2S32 Vec2S32_Mult(Vec2S32 a, Vec2S32 b);
Vec2S32 Vec2S32_Div(Vec2S32 a, Vec2S32 b);
Vec2S32 Vec2S32_AddScalar(Vec2S32 a, S32 b);
Vec2S32 Vec2S32_SubScalar(Vec2S32 a, S32 b);
Vec2S32 Vec2S32_DivScalar(Vec2S32 a, S32 b);
Vec2S32 Vec2S32_MultScalar(Vec2S32 a, S32 b);
F32 Vec2S32_Dot(Vec2S32 a, Vec2S32 b);
F32 Vec2S32_Magnitude(Vec2S32 a);
F32 Vec2S32_SqrMagnitude(Vec2S32 a);
Vec2S32 Vec2S32_Normalize(Vec2S32 a);
Vec2S32 Vec2S32_Lerp(Vec2S32 a, Vec2S32 b, F32 t);

// NOTE(calco): -- Vector3 Helper Functions --
Vec3F32 Vec3F32_Make(F32 a, F32 b, F32 c);
Vec3F32 Vec3F32_Add(Vec3F32 a, Vec3F32 b);
Vec3F32 Vec3F32_Sub(Vec3F32 a, Vec3F32 b);
Vec3F32 Vec3F32_Mult(Vec3F32 a, Vec3F32 b);
Vec3F32 Vec3F32_Div(Vec3F32 a, Vec3F32 b);
Vec3F32 Vec3F32_AddScalar(Vec3F32 a, F32 b);
Vec3F32 Vec3F32_SubScalar(Vec3F32 a, F32 b);
Vec3F32 Vec3F32_DivScalar(Vec3F32 a, F32 b);
Vec3F32 Vec3F32_MultScalar(Vec3F32 a, F32 b);
F32 Vec3F32_Dot(Vec3F32 a, Vec3F32 b);
Vec3F32 Vec3F32_Cross(Vec3F32 a, Vec3F32 b);
F32 Vec3F32_Magnitude(Vec3F32 a);
F32 Vec3F32_SqrMagnitude(Vec3F32 a);
Vec3F32 Vec3F32_Normalize(Vec3F32 a);
Vec3F32 Vec3F32_Lerp(Vec3F32 a, Vec3F32 b, F32 t);

Vec3S32 Vec3S32_Make(S32 a, S32 b, S32 c);
Vec3S32 Vec3S32_Add(Vec3S32 a, Vec3S32 b);
Vec3S32 Vec3S32_Sub(Vec3S32 a, Vec3S32 b);
Vec3S32 Vec3S32_Mult(Vec3S32 a, Vec3S32 b);
Vec3S32 Vec3S32_Div(Vec3S32 a, Vec3S32 b);
Vec3S32 Vec3S32_AddScalar(Vec3S32 a, S32 b);
Vec3S32 Vec3S32_SubScalar(Vec3S32 a, S32 b);
Vec3S32 Vec3S32_DivScalar(Vec3S32 a, S32 b);
Vec3S32 Vec3S32_MultScalar(Vec3S32 a, S32 b);
F32 Vec3S32_Dot(Vec3S32 a, Vec3S32 b);
F32 Vec3S32_Magnitude(Vec3S32 a);
F32 Vec3S32_SqrMagnitude(Vec3S32 a);
Vec3S32 Vec3S32_Normalize(Vec3S32 a);
Vec3S32 Vec3S32_Lerp(Vec3S32 a, Vec3S32 b, F32 t);

// NOTE(calco): -- Matrix Helper Functions --
Mat3x3F32 Mat3x3_Identity();

Mat3x3F32 Mat3x3_MakeValue(F32 value);
Mat3x3F32 Mat3x3_MakeTransform(Vec2F32 translate);
Mat3x3F32 Mat3x3_MakeScale(Vec2F32 scale);
Mat3x3F32 Mat3x3_MakeRotation(F32 radians);

Mat3x3F32 Mat3x3_Mult(Mat3x3F32 a, Mat3x3F32 b);
Mat3x3F32 Mat3x3_Scale(Mat3x3F32 a, F32 scale);

Mat3x3F32 Mat3x3_Transpose(Mat3x3F32 mat);

// Matrix4x4
Mat4x4F32 Mat4x4_Identity();

Mat4x4F32 Mat4x4_MakeValue(F32 value);
Mat4x4F32 Mat4x4_MakeTranslate(Vec3F32 translate);
Mat4x4F32 Mat4x4_MakeScale(Vec3F32 scale);
Mat4x4F32 Mat4x4_MakeRotation(Vec3F32 axis, F32 radians);
// TODO(calco): Add some functions to create a 4x4 ortographic / perspective

Mat4x4F32 Mat4x4_Mult(Mat4x4F32 a, Mat4x4F32 b);
Mat4x4F32 Mat4x4_Scale(Mat4x4F32 a, F32 scale);

Mat4x4F32 Mat4x4_Transpose(Mat4x4F32 mat);

// NOTE(calco): -- Matrix Vector Math --
Vec2F32 Vec2F32_ApplyMatrix(Mat3x3F32 mat, Vec2F32 vec);
Vec3F32 Vec3F32_ApplyMatrix(Mat4x4F32 mat, Vec3F32 vec);

// NOTE(calco): -- Static Vector 2s --
#define Vec2F32_One   Vec2F32_Make(1.0f, 1.0f)
#define Vec2F32_Zero  Vec2F32_Make(0.0f, 0.0f)
#define Vec2F32_Right Vec2F32_Make(1.0f, 0.0f)
#define Vec2F32_Up    Vec2F32_Make(0.0f, 1.0f)
#define Vec2F32_Left  Vec2F32_Make(-1.0f, 0.0f)
#define Vec2F32_Down  Vec2F32_Make(0.0f, -1.0f)

#define Vec2S32_One   Vec2S32_Make(1, 1)
#define Vec2S32_Zero  Vec2S32_Make(0, 0)
#define Vec2S32_Right Vec2S32_Make(1, 0)
#define Vec2S32_Up    Vec2S32_Make(0, 1)
#define Vec2S32_Left  Vec2S32_Make(-1, 0)
#define Vec2S32_Down  Vec2S32_Make(0, -1)

// NOTE(calco): -- Static Vector 3s --
#define Vec3F32_One     Vec3F32_Make(1.0f, 1.0f, 1.0f)
#define Vec3F32_Zero    Vec3F32_Make(0.0f, 0.0f, 0.0f)
#define Vec3F32_Forward Vec3F32_Make(0.0f, 0.0f, 1.0f)
#define Vec3F32_Back    Vec3F32_Make(0.0f, 0.0f, -1.0f)
#define Vec3F32_Right   Vec3F32_Make(1.0f, 0.0f, 0.0f)
#define Vec3F32_Up      Vec3F32_Make(0.0f, 1.0f, 0.0f)
#define Vec3F32_Left    Vec3F32_Make(-1.0f, 0.0f, 0.0f)
#define Vec3F32_Down    Vec3F32_Make(0.0f, -1.0f, 0.0f)

#define Vec3S32_One     Vec3S32_Make(1, 1, 1)
#define Vec3S32_Zero    Vec3S32_Make(0, 0, 0)
#define Vec3F32_Forward Vec3F32_Make(0, 0, 1)
#define Vec3F32_Back    Vec3F32_Make(0, 0, -1)
#define Vec3S32_Right   Vec3S32_Make(1, 0, 0)
#define Vec3S32_Up      Vec3S32_Make(0, 1, 0)
#define Vec3S32_Left    Vec3S32_Make(-1, 0, 0)
#define Vec3S32_Down    Vec3S32_Make(0, -1, 0)

// NOTE(calco): -- Quaternion Helper Functions --
QuatF32 QuatF32_Make(F32 x, F32 y, F32 z, F32 w);
QuatF32 QuatF32_MakeFromAxisAngle(Vec3F32 axis, F32 radians);

QuatF32 QuatF32_Add(QuatF32 a, QuatF32 b);
QuatF32 QuatF32_Sub(QuatF32 a, QuatF32 b);
QuatF32 QuatF32_Mult(QuatF32 a, QuatF32 b);
QuatF32 QuatF32_MultScalar(QuatF32 a, F32 f);
QuatF32 QuatF32_Normalize(QuatF32 quat);
F32 QuatF32_Dot(QuatF32 a, QuatF32 b);
QuatF32 QuatF32_Lerp(QuatF32 a, QuatF32 b, F32 t);
Mat4x4F32 QuatF32_Mat4x4FromQuatF32(QuatF32 quat);

#endif