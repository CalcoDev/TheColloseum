#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "base_types.h"
#include <math.h>

// NOTE(calco): -- Constants --
static F32 InfinityF32 = INFINITY;

static F32 PiF32             = 3.1415926535897f;
static F32 EulersConstantF32 = 2.7182818284590452353602874713527f;

static F64 PiF64             = 3.1415926535897;
static F64 EulersConstantF64 = 2.7182818284590452353602874713527;

// NOTE(calco): -- Base Math --
#define FloorF32(f)      floorf(f);
#define CeilF32(f)       ceilf(f);
#define RoundF32(f)      roundf(f);
#define DegToRadF32(deg) ((PiF32 / 180.f) * (deg))
#define RadToDegF32(rad) ((180.f / PiF32) * (rad))
#define SquareRootF32(f) sqrtf(f);
#define SinF32(f)        sinf(f);
#define CosF32(f)        cosf(f);
#define TanF32(f)        tanf(f);

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

// NOTE(calco): -- Vector2 Helper Functions --
// yes yes, wrong naming convention, should be V2F32Add(), but for usability
// and readabilitys sake it will be AddV2F32();

Vec2F32 V2F32(F32 a, F32 b);
Vec2F32 V2F32_Add(Vec2F32 a, Vec2F32 b);
Vec2F32 V2F32_Sub(Vec2F32 a, Vec2F32 b);
Vec2F32 V2F32_Mult(Vec2F32 a, Vec2F32 b);
Vec2F32 V2F32_Div(Vec2F32 a, Vec2F32 b);
Vec2F32 V2F32_Scale(Vec2F32 a, F32 b);
F32 V2F32_Dot(Vec2F32 a, Vec2F32 b);
F32 V2F32_Magnitude(Vec2F32 a);
F32 V2F32_SqrMagnitude(Vec2F32 a);
Vec2F32 V2F32_Normalize(Vec2F32 a);
Vec2F32 V2F32_Lerp(Vec2F32 a, Vec2F32 b, F32 t);

Vec2S32 V2S32(S32 a, S32 b);
Vec2S32 V2S32_Add(Vec2S32 a, Vec2S32 b);
Vec2S32 V2S32_Sub(Vec2S32 a, Vec2S32 b);
Vec2S32 V2S32_Mult(Vec2S32 a, Vec2S32 b);
Vec2S32 V2S32_Div(Vec2S32 a, Vec2S32 b);
Vec2S32 V2S32_Scale(Vec2S32 a, S32 b);
F32 V2S32_Dot(Vec2S32 a, Vec2S32 b);
F32 V2S32_Magnitude(Vec2S32 a);
F32 V2S32_SqrMagnitude(Vec2S32 a);
Vec2S32 V2S32_Normalize(Vec2S32 a);
Vec2S32 V2S32_Lerp(Vec2S32 a, Vec2S32 b, F32 t);

// NOTE(calco): -- Vector3 Helper Functions --
Vec3F32 V3F32(F32 a, F32 b, F32 c);
Vec3F32 V3F32_Add(Vec3F32 a, Vec3F32 b);
Vec3F32 V3F32_Sub(Vec3F32 a, Vec3F32 b);
Vec3F32 V3F32_Mult(Vec3F32 a, Vec3F32 b);
Vec3F32 V3F32_Div(Vec3F32 a, Vec3F32 b);
Vec3F32 V3F32_Scale(Vec3F32 a, F32 b);
F32 V3F32_Dot(Vec3F32 a, Vec3F32 b);
F32 V3F32_Magnitude(Vec3F32 a);
F32 V3F32_SqrMagnitude(Vec3F32 a);
Vec3F32 V3F32_Normalize(Vec3F32 a);
Vec3F32 V3F32_Lerp(Vec3F32 a, Vec3F32 b, F32 t);

Vec3S32 V3S32(S32 a, S32 b, S32 c);
Vec3S32 V3S32_Add(Vec3S32 a, Vec3S32 b);
Vec3S32 V3S32_Sub(Vec3S32 a, Vec3S32 b);
Vec3S32 V3S32_Mult(Vec3S32 a, Vec3S32 b);
Vec3S32 V3S32_Div(Vec3S32 a, Vec3S32 b);
Vec3S32 V3S32_Scale(Vec3S32 a, S32 b);
F32 V3S32_Dot(Vec3S32 a, Vec3S32 b);
F32 V3S32_Magnitude(Vec3S32 a);
F32 V3S32_SqrMagnitude(Vec3S32 a);
Vec3S32 V3S32_Normalize(Vec3S32 a);
Vec3S32 V3S32_Lerp(Vec3S32 a, Vec3S32 b, F32 t);

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
Mat4x4F32 Mat4x4_MakeTransform(Vec3F32 translate);
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
#define V2F32_One   V2F32(1.0f, 1.0f)
#define V2F32_Zero  V2F32(0.0f, 0.0f)
#define V2F32_Right V2F32(1.0f, 0.0f)
#define V2F32_Up    V2F32(0.0f, 1.0f)
#define V2F32_Left  V2F32(-1.0f, 0.0f)
#define V2F32_Down  V2F32(0.0f, -1.0f)

#define V2S32_One   V2S32(1, 1)
#define V2S32_Zero  V2S32(0, 0)
#define V2S32_Right V2S32(1, 0)
#define V2S32_Up    V2S32(0, 1)
#define V2S32_Left  V2S32(-1, 0)
#define V2S32_Down  V2S32(0, -1)

// NOTE(calco): -- Static Vector 3s --
#define V3F32_One     V3F32(1.0f, 1.0f, 1.0f)
#define V3F32_Zero    V3F32(0.0f, 0.0f, 0.0f)
#define V3F32_Forward V3F32(0.0f, 0.0f, 1.0f)
#define V3F32_Back    V3F32(0.0f, 0.0f, -1.0f)
#define V3F32_Right   V3F32(1.0f, 0.0f, 0.0f)
#define V3F32_Up      V3F32(0.0f, 1.0f, 0.0f)
#define V3F32_Left    V3F32(-1.0f, 0.0f, 0.0f)
#define V3F32_Down    V3F32(0.0f, -1.0f, 0.0f)

#define V3S32_One     V3S32(1, 1, 1)
#define V3S32_Zero    V3S32(0, 0, 0)
#define V3F32_Forward V3F32(0, 0, 1)
#define V3F32_Back    V3F32(0, 0, -1)
#define V3S32_Right   V3S32(1, 0, 0)
#define V3S32_Up      V3S32(0, 1, 0)
#define V3S32_Left    V3S32(-1, 0, 0)
#define V3S32_Down    V3S32(0, -1, 0)

#endif