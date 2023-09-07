#ifndef BASE_STRING_H
#define BASE_STRING_H

#include "base_types.h"

/// @brief Represents a string. NOT NULL TERMINATED
typedef struct StringU8
{
  U8* data;
  U64 size;
} StringU8;

// Init Functions
StringU8 Str8Init(U8* data, U64 size);
#define Str8Lit(ss_lit) String8Init((U8*)(s_lit), sizeof(s_lit))

// Conversions
U8* Str8CString(StringU8 string);

// Helper Functions
StringU8 Str8Prefix(StringU8 string, U64 size);
StringU8 Str8Postfix(StringU8 string, U64 size);

#endif