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

F32 LerpF32(F32 a, F32 b, F32 t);
F32 LerpS32(S32 a, S32 b, F32 t)

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

// NOTE(calco): -- Vector2 Helper Functions --
// yes yes, wrong naming convention, should be V2F32Add(), but for usability
// and readabilitys sake it will be AddV2F32();

Vec2F32 V2F32(F32 a, F32 b);
Vec2F32 AddV2F32(Vec2F32 a, Vec2F32 b);
Vec2F32 SubV2F32(Vec2F32 a, Vec2F32 b);
Vec2F32 MultV2F32(Vec2F32 a, Vec2F32 b);
Vec2F32 DivV2F32(Vec2F32 a, Vec2F32 b);
Vec2F32 ScaleV2F32(Vec2F32 a, F32 b);
F32 DotV2F32(Vec2F32 a, Vec2F32 b);
F32 MagnitudeV2F32(Vec2F32 a);
F32 SqrMagnitudeV2F32(Vec2F32 a);
Vec2F32 NormalizeV2F32(Vec2F32 a);
Vec2F32 LerpV2F32(Vec2F32 a, Vec2F32 b, F32 t);

Vec2S32 V2S32(S32 a, S32 b);
Vec2S32 AddV2S32(Vec2S32 a, Vec2S32 b);
Vec2S32 SubV2S32(Vec2S32 a, Vec2S32 b);
Vec2S32 MultV2S32(Vec2S32 a, Vec2S32 b);
Vec2S32 DivV2S32(Vec2S32 a, Vec2S32 b);
Vec2S32 ScaleV2S32(Vec2S32 a, S32 b);
F32 DotV2S32(Vec2S32 a, Vec2S32 b);
F32 MagnitudeV2S32(Vec2S32 a);
F32 SqrMagnitudeV2S32(Vec2S32 a);
Vec2S32 NormalizeV2S32(Vec2S32 a);
Vec2S32 LerpV2S32(Vec2S32 a, Vec2S32 b, F32 t);

// NOTE(calco): -- Vector3 Helper Functions --
Vec3F32 V3F32(F32 a, F32 b, F32 c);
Vec3F32 AddV3F32(Vec3F32 a, Vec3F32 b);
Vec3F32 SubV3F32(Vec3F32 a, Vec3F32 b);
Vec3F32 MultV3F32(Vec3F32 a, Vec3F32 b);
Vec3F32 DivV3F32(Vec3F32 a, Vec3F32 b);
Vec3F32 ScaleV3F32(Vec3F32 a, F32 b);
F32 DotV3F32(Vec3F32 a, Vec3F32 b);
F32 MagnitudeV3F32(Vec3F32 a);
F32 SqrMagnitudeV3F32(Vec3F32 a);
Vec3F32 NormalizeV3F32(Vec3F32 a);
Vec3F32 LerpV3F32(Vec3F32 a, Vec3F32 b, F32 t);

Vec3S32 V3S32(S32 a, S32 b);
Vec3S32 AddV3S32(Vec3S32 a, Vec3S32 b);
Vec3S32 SubV3S32(Vec3S32 a, Vec3S32 b);
Vec3S32 MultV3S32(Vec3S32 a, Vec3S32 b);
Vec3S32 DivV3S32(Vec3S32 a, Vec3S32 b);
Vec3S32 ScaleV3S32(Vec3S32 a, S32 b);
F32 DotV3S32(Vec3S32 a, Vec3S32 b);
F32 MagnitudeV3S32(Vec3S32 a);
F32 SqrMagnitudeV3S32(Vec3S32 a);
Vec3S32 NormalizeV3S32(Vec3S32 a);
Vec3S32 LerpV3S32(Vec3S32 a, Vec3S32 b, F32 t);

#endif