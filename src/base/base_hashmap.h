#ifndef BASE_HASHMAP_H
#define BASE_HASHMAP_H

#include "base_memory.h";
#include "base_string.h";
#include "base_types.h";

// we dont do collisions for now

// NOTE(calco): -- Hashmap --

// THIS IS SCUFFED. I DO NOT THINK PREPROCESSORS ARE SUPPOSED TO BE USED THIS
// WAY HOWEVER IT MAKES GENERICS :SKULL:

#define Hashmap(key_type, value_type) Hashmap_##key_type##_To_##value_type
#define Hashmap_Key(key_type, value_type)                                      \
  Hashmap_##key_type##_To_##value_type##_Key
#define Hashmap_Value(key_type, value_type)                                    \
  Hashmap_##key_type##_To_##value_type##_Value
#define Hashmap_Entry(key_type, value_type)                                    \
  Hashmap_##key_type##_To_##value_type##_Entry

#define Hashmap_Init(                                                          \
    key_type, value_type, arena, hashmap, bucket_count, hash_function,         \
    null_elem_function                                                         \
)                                                                              \
  Hashmap_##key_type##_To_##value_type##_Init(                                 \
      arena, hashmap, bucket_count, hash_function, null_elem_function          \
  )
#define Hashmap_Add(key_type, value_type, hashmap, key, value)                 \
  Hashmap_##key_type##_To_##value_type##_Add(hashmap, key, value)
#define Hashmap_Get(key_type, value_type, hashmap, key)                        \
  Hashmap_##key_type##_To_##value_type##_Get(hashmap, key)
#define Hashmap_TryGet(key_type, value_type, hashmap, key, out)                \
  Hashmap_##key_type##_To_##value_type##_TryGet(hashmap, key, out)

#define Hashmap_CreatePrototype(key_type, value_type)                          \
  typedef key_type Hashmap_##key_type##_To_##value_type##_Key;                 \
  typedef value_type Hashmap_##key_type##_To_##value_type##_Value;             \
                                                                               \
  typedef struct Hashmap_##key_type##_To_##value_type##_Entry                  \
  {                                                                            \
    Hashmap_##key_type##_To_##value_type##_Key key;                            \
    Hashmap_##key_type##_To_##value_type##_Value value;                        \
  } Hashmap_##key_type##_To_##value_type##_Entry;                              \
                                                                               \
  typedef value_type (*Hashmap_##key_type##_To_##value_type##Function)(        \
      Hashmap_##key_type##_To_##value_type##_Key, U64                          \
  );                                                                           \
  typedef B32 (*Hashmap_##key_type##_To_##value_type##NullElementFunction)(    \
      Hashmap_##key_type##_To_##value_type##_Entry                             \
  );                                                                           \
                                                                               \
  typedef struct Hashmap_##key_type##_To_##value_type##                        \
  {                                                                            \
    U64 bucket_count;                                                          \
    Hashmap_##key_type##_To_##value_type##_Entry* entries;                     \
    Hashmap_##key_type##_To_##value_type##Function hash_function;              \
    Hashmap_##key_type##_To_##value_type##NullElementFunction                  \
        null_elem_function;                                                    \
  } Hashmap_##key_type##_To_##value_type##;                                    \
                                                                               \
  void Hashmap_##key_type##_To_##value_type##_Init(                            \
      Arena* arena, Hashmap_##key_type##_To_##value_type##* hashmap,           \
      U64 bucket_count,                                                        \
      Hashmap_##key_type##_To_##value_type##Function hash_function,            \
      Hashmap_##key_type##_To_##value_type##NullElementFunction                \
          null_elem_function                                                   \
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
      );                                                                       \
                                                                               \
  B32 Hashmap_##key_type##_To_##value_type##_TryGet(                           \
      Hashmap_##key_type##_To_##value_type##* hashmap,                         \
      Hashmap_##key_type##_To_##value_type##_Key key,                          \
      Hashmap_##key_type##_To_##value_type##_Value* out_value                  \
  );

#define Hashmap_Implement(key_type, value_type)                                \
  void Hashmap_##key_type##_To_##value_type##_Init(                            \
      Arena* arena, Hashmap_##key_type##_To_##value_type##* hashmap,           \
      U64 bucket_count,                                                        \
      Hashmap_##key_type##_To_##value_type##Function hash_function,            \
      Hashmap_##key_type##_To_##value_type##NullElementFunction                \
          null_elem_function                                                   \
  )                                                                            \
  {                                                                            \
    hashmap->bucket_count                             = bucket_count;          \
    Hashmap_##key_type##_To_##value_type##_Entry* mem = ArenaPush(             \
        arena,                                                                 \
        bucket_count * sizeof(Hashmap_##key_type##_To_##value_type##_Entry)    \
    );                                                                         \
    hashmap->entries            = mem;                                         \
    hashmap->hash_function      = hash_function;                               \
    hashmap->null_elem_function = null_elem_function;                          \
  }                                                                            \
                                                                               \
  void Hashmap_##key_type##_To_##value_type##_Add(                             \
      Hashmap_##key_type##_To_##value_type##* hashmap,                         \
      Hashmap_##key_type##_To_##value_type##_Key key,                          \
      Hashmap_##key_type##_To_##value_type##_Value value                       \
  )                                                                            \
  {                                                                            \
    U64 hash = hashmap->hash_function(key, hashmap->bucket_count);             \
    Hashmap_##key_type##_To_##value_type##_Entry entry = {0};                  \
    entry.value                                        = value;                \
    entry.key                                          = key;                  \
    *(hashmap->entries + hash)                         = entry;                \
  }                                                                            \
                                                                               \
  Hashmap_##key_type##_To_##value_type##_Value                                 \
      Hashmap_##key_type##_To_##value_type##_Get(                              \
          Hashmap_##key_type##_To_##value_type##* hashmap,                     \
          Hashmap_##key_type##_To_##value_type##_Key key                       \
      )                                                                        \
  {                                                                            \
    U64 hash = hashmap->hash_function(key, hashmap->bucket_count);             \
    return (hashmap->entries + hash)->value;                                   \
  }                                                                            \
                                                                               \
  B32 Hashmap_##key_type##_To_##value_type##_TryGet(                           \
      Hashmap_##key_type##_To_##value_type##* hashmap,                         \
      Hashmap_##key_type##_To_##value_type##_Key key,                          \
      Hashmap_##key_type##_To_##value_type##_Value* out_value                  \
  )                                                                            \
  {                                                                            \
    if (hashmap->bucket_count == 0)                                            \
      return 0;                                                                \
                                                                               \
    U64 hash = hashmap->hash_function(key, hashmap->bucket_count);             \
    if (hashmap->bucket_count <= hash)                                         \
      return 0;                                                                \
                                                                               \
    Hashmap_##key_type##_To_##value_type##_Entry* entry =                      \
        hashmap->entries + hash;                                               \
                                                                               \
    if (!hashmap->null_elem_function(*entry))                                  \
    {                                                                          \
      *out_value = entry->value;                                               \
      return 1;                                                                \
    }                                                                          \
    return 0;                                                                  \
  }

#endif