#ifndef BASE_HASHMAP_H
#define BASE_HASHMAP_H

#include "base_memory.h";
#include "base_string.h";
#include "base_types.h";

// we dont do collisions for now

// NOTE(calco): -- Hashmap --
typedef struct Hashmap_Pair_String8U64
{
  // TODO(calco): Should these be pointers?
  String8 key;
  U64 value;
} Hashmap_Pair_String8U64;

typedef U64 (*Hashmap_String8U64_HashFunction)(String8);

typedef struct Hashmap_String8U64
{
  Hashmap_Pair_String8U64* values;
  Hashmap_String8U64_HashFunction hash_function;
} Hashmap_String8U64;

void Hashmap_String8U64_Init(
    Arena* arena, Hashmap_String8U64* hashmap, U64 bucket_count,
    Hashmap_String8U64_HashFunction hash_function
);

void Hashmap_String8U64_Add(
    Hashmap_String8U64* hashmap, String8 key, U64 value
);

U64 Hashmap_String8U64_Get(Hashmap_String8U64* hashmap, String8 key);

#endif