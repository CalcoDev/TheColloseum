#ifndef BASE_HASHMAP_H
#define BASE_HASHMAP_H

#include "base_memory.h";
#include "base_string.h";
#include "base_types.h";

// we dont do collisions for now

// NOTE(calco): -- Hashmap --

// THIS IS SCUFFED. I DO NOT THINK PREPROCESSORS ARE SUPPOSED TO BE USED THIS
// WAY HOWEVER IT MAKES GENERICS :SKULL:

#define Hashmap_CreatePrototype(key_type, value_type)                          \
  typedef key_type Hashmap_##key_type##_To_##value_type##_Key;                 \
  typedef value_type Hashmap_##key_type##_To_##value_type##_Value;             \
                                                                               \
  typedef value_type (*Hashmap_##key_type##_To_##value_type##Function)(        \
      key_type                                                                 \
  );                                                                           \
                                                                               \
  typedef struct Hashmap_##key_type##_To_##value_type##                        \
  {                                                                            \
    ##value_type##* values;                                                    \
    Hashmap_##key_type##_To_##value_type##Function hash_function;              \
  } Hashmap_##key_type##_To_##value_type##;                                    \
                                                                               \
  void Hashmap_##key_type##_To_##value_type##_Init(                            \
      Arena* arena, Hashmap_##key_type##_To_##value_type##* hashmap,           \
      U64 bucket_count,                                                        \
      Hashmap_##key_type##_To_##value_type##Function hash_function             \
  );                                                                           \
                                                                               \
  void Hashmap_##key_type##_To_##value_type##_Add(                             \
      Hashmap_##key_type##_To_##value_type##* hashmap,                         \
      Hashmap_##key_type##_To_##value_type##_Key key,                          \
      Hashmap_##key_type##_To_##value_type##_Value value                       \
  );                                                                           \
                                                                               \
  Hashmap_##key_type##_To_##value_type##_Value                                 \
      Hashmap_##key_type##_To_##value_type##_Get(                              \
          Hashmap_##key_type##_To_##value_type##* hashmap,                     \
          Hashmap_##key_type##_To_##value_type##_Key key                       \
      );

#define Hashmap_Implement(key_type, value_type)                                \
  void Hashmap_##key_type##_To_##value_type##_Init(                            \
      Arena* arena, Hashmap_##key_type##_To_##value_type##* hashmap,           \
      U64 bucket_count,                                                        \
      Hashmap_##key_type##_To_##value_type##Function hash_function             \
  )                                                                            \
  {                                                                            \
    Hashmap_##key_type##_To_##value_type##_Value* mem =                        \
        ArenaPush(arena, bucket_count * sizeof(U64));                          \
    hashmap->values        = mem;                                              \
    hashmap->hash_function = hash_function;                                    \
  }                                                                            \
                                                                               \
  void Hashmap_##key_type##_To_##value_type##_Add(                             \
      Hashmap_##key_type##_To_##value_type##* hashmap,                         \
      Hashmap_##key_type##_To_##value_type##_Key key,                          \
      Hashmap_##key_type##_To_##value_type##_Value value                       \
  )                                                                            \
  {                                                                            \
    U64 hash                  = hashmap->hash_function(key);                   \
    *(hashmap->values + hash) = value;                                         \
  }                                                                            \
                                                                               \
  Hashmap_##key_type##_To_##value_type##_Value                                 \
      Hashmap_##key_type##_To_##value_type##_Get(                              \
          Hashmap_##key_type##_To_##value_type##* hashmap,                     \
          Hashmap_##key_type##_To_##value_type##_Key key                       \
      )                                                                        \
  {                                                                            \
    U64 hash = hashmap->hash_function(key);                                    \
    return *(hashmap->values + hash);                                          \
  }

#endif