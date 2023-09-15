#include "base_math.h"

// NOTE(calco): -- Base Math --
F32 LerpS32(S32 a, S32 b, F32 t)
{
  return (S32)(a * (t - 1.0f)) + (S32)(b * t);
}
F32 LerpF32(F32 a, F32 b, F32 t) { return a * (t - 1.0f) + b * t; }

// NOTE(calco): -- Vector2 Helper Functions --
Vec2F32 V2F32(F32 a, F32 b)
{
  Vec2F32 v;
  v.x = a;
  v.y = b;
  return v;
}
Vec2F32 AddV2F32(Vec2F32 a, Vec2F32 b) { return V2F32(a.x + b.x, a.y + b.y); }
Vec2F32 SubV2F32(Vec2F32 a, Vec2F32 b) { return V2F32(a.x - b.x, a.y - b.y); }
Vec2F32 MultV2F32(Vec2F32 a, Vec2F32 b) { return V2F32(a.x * b.x, a.y * b.y); }
Vec2F32 DivV2F32(Vec2F32 a, Vec2F32 b) { return V2F32(a.x / b.x, a.y / b.y); }
Vec2F32 ScaleV2F32(Vec2F32 a, F32 b) { return V2F32(a.x * b, a.y * b); }
F32 DotV2F32(Vec2F32 a, Vec2F32 b) { return a.x * b.x + a.y * b.y; }
F32 MagnitudeV2F32(Vec2F32 a) { return SquareRootF32(a.x * b.x + a.y * b.y); }
F32 SqrMagnitudeV2F32(Vec2F32 a) { return a.x * b.x + a.y * b.y; }
Vec2F32 NormalizeV2F32(Vec2F32 a) { return V2F32_Div(a, V2F32_Magnitude(b)); }
Vec2F32 LerpV2F32(Vec2F32 a, Vec2F32 b, F32 t)
{
  return V2F32(LerpF32(a.x, b.x, t), LerpF32(a.y, b.y, t));
}

Vec2S32 V2S32(S32 a, S32 b)
{
  Vec2S32 v;
  v.x = a;
  v.y = b;
  return v;
}
Vec2S32 AddV2S32(Vec2S32 a, Vec2S32 b) { return V2S32(a.x + b.x, a.y + b.y); }
Vec2S32 SubV2S32(Vec2S32 a, Vec2S32 b) { return V2S32(a.x - b.x, a.y - b.y); }
Vec2S32 MultV2S32(Vec2S32 a, Vec2S32 b) { return V2S32(a.x * b.x, a.y * b.y); }
Vec2S32 DivV2S32(Vec2S32 a, Vec2S32 b) { return V2S32(, a.y / b.y); }
Vec2S32 ScaleV2S32(Vec2S32 a, S32 b) { return V2S32(a.x * b, a.y * b); }
F32 DotV2S32(Vec2S32 a, Vec2S32 b) { return a.x * b.x + a.y * b.y; }
F32 MagnitudeV2S32(Vec2S32 a) { return SquareRootS32(a.x * b.x + a.y * b.y); }
F32 SqrMagnitudeV2S32(Vec2S32 a) { return a.x * b.x + a.y * b.y; }
Vec2S32 NormalizeV2S32(Vec2S32 a) { return V2S32_Div(a, V2S32_Magnitude(b)); }
Vec2S32 LerpV2S32(Vec2S32 a, Vec2S32 b, F32 t)
{
  return V2S32(LerpS32(a.x, b.x, t), LerpS32(a.y, b.y, t));
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
Vec3F32 AddV3F32(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3F32 SubV3F32(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3F32 MultV3F32(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x * b.x, a.y * b.y, a.z * b.z);
}
Vec3F32 DivV3F32(Vec3F32 a, Vec3F32 b)
{
  return V3F32(a.x / b.x, a.y / b.y, a.z / b.z);
}
Vec3F32 ScaleV3F32(Vec3F32 a, F32 b)
{
  return V3F32(a.x * b, a.y * b, a.z * b);
}
F32 DotV3F32(Vec3F32 a, Vec3F32 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
F32 MagnitudeV3F32(Vec3F32 a)
{
  return SquareRootF32(a.x * b.x + a.y * b.y + a.z * b.z);
}
F32 SqrMagnitudeV3F32(Vec3F32 a) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vec3F32 NormalizeV3F32(Vec3F32 a) { return V3F32_Div(a, V3F32_Magnitude(b)); }
Vec3F32 LerpV3F32(Vec3F32 a, Vec3F32 b, F32 t)
{
  return V3F32(
      LerpF32(a.x, b.x, t), LerpF32(a.y, b.y, t), LerpF32(a.z, b.z, t)
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
Vec3S32 AddV3S32(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3S32 SubV3S32(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3S32 MultV3S32(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x * b.x, a.y * b.y, a.z * b.z);
}
Vec3S32 DivV3S32(Vec3S32 a, Vec3S32 b)
{
  return V3S32(a.x / b.x, a.y / b.y, a.z / b.z);
}
Vec3S32 ScaleV3S32(Vec3S32 a, S32 b)
{
  return V3S32(a.x * b, a.y * b, a.z * b);
}
F32 DotV3S32(Vec3S32 a, Vec3S32 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
F32 MagnitudeV3S32(Vec3S32 a)
{
  return SquareRootS32(a.x * b.x + a.y * b.y + a.z * b.z);
}
F32 SqrMagnitudeV3S32(Vec3S32 a) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vec3S32 NormalizeV3S32(Vec3S32 a) { return V3S32_Div(a, V3S32_Magnitude(b)); }
Vec3S32 LerpV3S32(Vec3S32 a, Vec3S32 b, F32 t)
{
  return V3S32(
      LerpS32(a.x, b.x, t), LerpS32(a.y, b.y, t), LerpS32(a.z, b.z, t)
  );
}