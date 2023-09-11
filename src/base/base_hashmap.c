#include "base_hashmap.h"

void Hashmap_String8_To_U64_Init(
    Arena* arena, Hashmap_String8_To_U64* hashmap, U64 bucket_count,
    Hashmap_String8_To_U64Function hash_function
)
{
  void* mem = ArenaPush(arena, bucket_count * sizeof(U64));

  hashmap->values        = (U64*)mem;
  hashmap->hash_function = hash_function;
}

void Hashmap_String8_To_U64_Add(
    Hashmap_String8_To_U64* hashmap, String8 key, U64 value
)
{
  U64 hash                  = hashmap->hash_function(key);
  *(hashmap->values + hash) = value;
}

U64 Hashmap_String8_To_U64_Get(Hashmap_String8_To_U64* hashmap, String8 key)
{
  U64 hash = hashmap->hash_function(key);
  return *(hashmap->values + hash);
}