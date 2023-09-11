#ifndef BASE_HASHMAP_H
#define BASE_HASHMAP_H

#include "base_memory.h";
#include "base_string.h";
#include "base_types.h";

// we dont do collisions for now

// NOTE(calco): -- Hashmap --

// THIS IS SCUFFED. I DO NOT THINK PREPROCESSORS ARE SUPPOSED TO BE USED THIS
// WAY HOWEVER IT MAKES GENERICS :SKULL:

// #define Hashmap_CreateProrotype(key_type, value_type)\
// typedef key_type Hashmap_##key_type##_To_##value_type##_Key;\
// typedef value_type Hashmap_##key_type##_To_##value_type##_Value;\
// \
// typedef struct Hashmap_

typedef U64 (*Hashmap_String8U64_HashFunction)(String8);

typedef struct Hashmap_String8U64
{
  U64* values;
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