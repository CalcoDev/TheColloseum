#ifndef BASE_STRING_H
#define BASE_STRING_H

#include "base_memory.h"
#include "base_types.h"

/// @brief Represents a string. NOT NULL TERMINATED
typedef struct String8
{
  U8* data;
  U64 size;
} String8;

#define Str8Expand(s) ((s).data), (U64)((s).size)

// Init Functions
String8 Str8Init(U8* data, U64 size);
String8 Str8InitArena(Arena* arena, U8* data, U64 size);

#define Str8Lit(s_lit) ((String8){(U8*)(s_lit), sizeof(s_lit) - 1})
#define Str8LitArena(arena, s_lit)                                             \
  Str8InitArena((arena), Str8Expand(Str8Lit(s_lit)))

// Conversions
U8* Str8CString(String8 string);

// Helper Functions
String8 Str8Prefix(String8 string, U64 size);
String8 Str8Postfix(String8 string, U64 size);

#endif