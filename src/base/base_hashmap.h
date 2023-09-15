#ifndef BASEHASHMAPH
#define BASEHASHMAPH

#include "basememory.h";
#include "basestring.h";
#include "basetypes.h";

// we dont do collisions for now

// NOTE(calco): -- Hashmap --

// THIS IS SCUFFED. I DO NOT THINK PREPROCESSORS ARE SUPPOSED TO BE USED THIS
// WAY HOWEVER IT MAKES GENERICS :SKULL:

#define Hashmap(keytype, valuetype)      Hashmap##keytype##To##valuetype
#define HashmapKey(keytype, valuetype)   Hashmap##keytype##To##valuetype##Key
#define HashmapValue(keytype, valuetype) Hashmap##keytype##To##valuetype##Value
#define HashmapEntry(keytype, valuetype) Hashmap##keytype##To##valuetype##Entry

#define HashmapInit(                                                           \
    keytype, valuetype, arena, hashmap, bucketcount, hashfunction,             \
    nullelemfunction                                                           \
)                                                                              \
  Hashmap##keytype##To##valuetype##Init(                                       \
      arena, hashmap, bucketcount, hashfunction, nullelemfunction              \
  )
#define HashmapAdd(keytype, valuetype, hashmap, key, value)                    \
  Hashmap##keytype##To##valuetype##Add(hashmap, key, value)
#define HashmapGet(keytype, valuetype, hashmap, key)                           \
  Hashmap##keytype##To##valuetype##Get(hashmap, key)
#define HashmapTryGet(keytype, valuetype, hashmap, key, out)                   \
  Hashmap##keytype##To##valuetype##TryGet(hashmap, key, out)

#define HashmapCreatePrototype(keytype, valuetype)                             \
  typedef keytype Hashmap##keytype##To##valuetype##Key;                        \
  typedef valuetype Hashmap##keytype##To##valuetype##Value;                    \
                                                                               \
  typedef struct Hashmap##keytype##To##valuetype##Entry                        \
  {                                                                            \
    Hashmap##keytype##To##valuetype##Key key;                                  \
    Hashmap##keytype##To##valuetype##Value value;                              \
  } Hashmap##keytype##To##valuetype##Entry;                                    \
                                                                               \
  typedef valuetype (*Hashmap##keytype##To##valuetype##Function)(              \
      Hashmap##keytype##To##valuetype##Key, U64                                \
  );                                                                           \
  typedef B32 (*Hashmap##keytype##To##valuetype##NullElementFunction)(         \
      Hashmap##keytype##To##valuetype##Entry                                   \
  );                                                                           \
                                                                               \
  typedef struct Hashmap##keytype##To##valuetype##                             \
  {                                                                            \
    U64 bucketcount;                                                           \
    Hashmap##keytype##To##valuetype##Entry* entries;                           \
    Hashmap##keytype##To##valuetype##Function hashfunction;                    \
    Hashmap##keytype##To##valuetype##NullElementFunction nullelemfunction;     \
  } Hashmap##keytype##To##valuetype##;                                         \
                                                                               \
  void Hashmap##keytype##To##valuetype##Init(                                  \
      Arena* arena, Hashmap##keytype##To##valuetype##* hashmap,                \
      U64 bucketcount, Hashmap##keytype##To##valuetype##Function hashfunction, \
      Hashmap##keytype##To##valuetype##NullElementFunction nullelemfunction    \
  );                                                                           \
                                                                               \
  void Hashmap##keytype##To##valuetype##Add(                                   \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key,                                \
      Hashmap##keytype##To##valuetype##Value value                             \
  );                                                                           \
                                                                               \
  Hashmap##keytype##To##valuetype##Value Hashmap##keytype##To##valuetype##Get( \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key                                 \
  );                                                                           \
                                                                               \
  B32 Hashmap##keytype##To##valuetype##TryGet(                                 \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key,                                \
      Hashmap##keytype##To##valuetype##Value* outvalue                         \
  );

#define HashmapImplement(keytype, valuetype)                                   \
  void Hashmap##keytype##To##valuetype##Init(                                  \
      Arena* arena, Hashmap##keytype##To##valuetype##* hashmap,                \
      U64 bucketcount, Hashmap##keytype##To##valuetype##Function hashfunction, \
      Hashmap##keytype##To##valuetype##NullElementFunction nullelemfunction    \
  )                                                                            \
  {                                                                            \
    hashmap->bucketcount                        = bucketcount;                 \
    Hashmap##keytype##To##valuetype##Entry* mem = ArenaPush(                   \
        arena, bucketcount * sizeof(Hashmap##keytype##To##valuetype##Entry)    \
    );                                                                         \
    hashmap->entries          = mem;                                           \
    hashmap->hashfunction     = hashfunction;                                  \
    hashmap->nullelemfunction = nullelemfunction;                              \
  }                                                                            \
                                                                               \
  void Hashmap##keytype##To##valuetype##Add(                                   \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key,                                \
      Hashmap##keytype##To##valuetype##Value value                             \
  )                                                                            \
  {                                                                            \
    U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);               \
    Hashmap##keytype##To##valuetype##Entry entry = {0};                        \
    entry.value                                  = value;                      \
    entry.key                                    = key;                        \
    *(hashmap->entries + hash)                   = entry;                      \
  }                                                                            \
                                                                               \
  Hashmap##keytype##To##valuetype##Value Hashmap##keytype##To##valuetype##Get( \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key                                 \
  )                                                                            \
  {                                                                            \
    U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);               \
    return (hashmap->entries + hash)->value;                                   \
  }                                                                            \
                                                                               \
  B32 Hashmap##keytype##To##valuetype##TryGet(                                 \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key,                                \
      Hashmap##keytype##To##valuetype##Value* outvalue                         \
  )                                                                            \
  {                                                                            \
    if (hashmap->bucketcount == 0)                                             \
      return 0;                                                                \
                                                                               \
    U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);               \
    if (hashmap->bucketcount <= hash)                                          \
      return 0;                                                                \
                                                                               \
    Hashmap##keytype##To##valuetype##Entry* entry = hashmap->entries + hash;   \
                                                                               \
    if (!hashmap->nullelemfunction(*entry))                                    \
    {                                                                          \
      *outvalue = entry->value;                                                \
      return 1;                                                                \
    }                                                                          \
    return 0;                                                                  \
  }

#endif