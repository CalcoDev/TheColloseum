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