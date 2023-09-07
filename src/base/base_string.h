#ifndef BASE_STRING_H
#define BASE_STRING_H

#include "base_memory.h"
#include "base_types.h"

/// @brief Represents a string. NOT NULL TERMINATED
typedef struct StringU8
{
  U8* data;
  U64 size;
} StringU8;

#define Str8Expand(s) ((s).data), (U64)((s).size)

// Init Functions
StringU8 Str8Init(U8* data, U64 size);
StringU8 Str8InitArena(Arena* arena, U8* data, U64 size);

#define Str8Lit(s_lit) ((StringU8){(U8*)(s_lit), sizeof(s_lit) - 1})
#define Str8LitArena(arena, s_lit)                                             \
  Str8InitArena((arena), Str8Expand(Str8Lit(s_lit)))

// Conversions
U8* Str8CString(StringU8 string);

// Helper Functions
StringU8 Str8Prefix(StringU8 string, U64 size);
StringU8 Str8Postfix(StringU8 string, U64 size);

#endif