#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "base_types.h"
#include <math.h>

// NOTE(calco): -- Constants --
static F32 InfinityF32 = INFINITY;

static F32 PiF32             = 3.1415926535897f;
static F32 EulersConstantF32 = 2.7182818284590452353602874713527f;

static F64 PiF64             = 3.1415926535897;
static F64 EulersConstantF32 = 2.7182818284590452353602874713527;

// NOTE(calco): -- Float Math --
#define FloorF32(f)      floorf(f);
#define CeilF32(f)       ceilf(f);
#define RoundF32(f)      roundf(f);
#define DegToRadF32(deg) ((PiF32 / 180.f) * (deg))
#define RadToDegF32(rad) ((180.f / PiF32) * (rad))
#define SquareRootF32(f) sqrtf(f);
#define SinF32(f)        sinf(f);
#define CosF32(f)        cosf(f);
#define TanF32(f)        tanf(f);

#endif