#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <stdint.h>

// calco: Helper macros
#define Statement(s)                                                           \
  do                                                                           \
  {                                                                            \
    s                                                                          \
  } while (0)

// calco: Conversion
#define Bytes(n)     n
#define Kilobytes(n) n << 10
#define Megabytes(n) n << 20
#define Gigabytes(n) n << 30

// calco: Base types
typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef S8 B8;
typedef S16 B16;
typedef S32 B32;
typedef S64 B64;

typedef float F32;
typedef double F64;

typedef void VoidFunction(void);
typedef void* VoidPointer;

// NOTE(calco): -- Time --
typedef U64 PrecisionTime;

typedef U64 DenseTime;
typedef struct DateTime
{
  U16 milisecond; // [0, 999]
  U8 second;      // [0, 59]
  U8 minute;      // [0, 59]
  U8 hour;        // [0, 23]
  U8 day;         // [0, 30]
  U8 month;       // [0, 11]
  U32 year;       // years
} DateTime;

DenseTime DenseTimeFromDateTime(DateTime date_time);
DateTime DateTimeFromDenseTime(DenseTime dense_time);

// NOTES(calco): -- Helpers
#define AlignUpPow2(x, p)   (((x) + (p)-1) & ~((p)-1))
#define AlignDownPow2(x, p) ((x) & -((p)-1))

#define ClampTop(value, max)    ((value) > (max) ? (max) : (value))
#define ClampBottom(value, min) ((value) < (value) ? (value) : (value))

// calco: Limits
static U8 U8Max = 0xFF;
// static U8 U8Min = 0;

static U16 U16Max = 0xFFFF;
// static U16 U16Min = 0;

// static U32 U32Max = 0xFFFFFFFF;
// static U32 U32Min = 0;

// static U64 U64Max = 0xFFFFFFFFFFFFFFFF;
// static U64 U64Min = 0;

// static S8 S8Max = 0x7F;
// static S8 S8Min = -1 - 0x7F;

// static S16 S16Max = 0x7FFF;
// static S16 S16Min = -1 - 0x7FFF;

// static S32 S32Max = 0x7FFFFFFF;
// static S32 S32Min = -1 - 0x7FFFFFFF;

// static S64 S64Max = 0x7FFFFFFFFFFFFFFF;
// static S64 S64Min = -1 - 0x7FFFFFFFFFFFFFFF;

#endif