#ifndef BASEHASHMAPH
#define BASEHASHMAPH

#include "base_memory.h";
#include "base_string.h";
#include "base_types.h";

// we dont do collisions for now

// NOTE(calco): -- Hashmap --

// THIS IS SCUFFED. I DO NOT THINK PREPROCESSORS ARE SUPPOSED TO BE USED THIS
// WAY HOWEVER IT MAKES GENERICS :SKULL:

U64 __HashmapLookup(U64 hash, S32 exp, S32 idx);

#define Hashmap(keytype, valuetype)      Hashmap##keytype##To##valuetype
#define HashmapKey(keytype, valuetype)   Hashmap##keytype##To##valuetype##Key
#define HashmapValue(keytype, valuetype) Hashmap##keytype##To##valuetype##Value
#define HashmapEntry(keytype, valuetype) Hashmap##keytype##To##valuetype##Entry
#define HashmapEntryPointer(keytype, valuetype)                                \
  Hashmap##keytype##To##valuetype##EntryPointer

#define HashmapInit(                                                           \
    keytype, valuetype, arena, hashmap, exp, hashfunction, nullelemfunction,   \
    equalelemfunction                                                          \
)                                                                              \
  Hashmap##keytype##To##valuetype##Init(                                       \
      arena, hashmap, exp, hashfunction, nullelemfunction, equalelemfunction   \
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
  typedef Hashmap##keytype##To##valuetype##Entry*                              \
      Hashmap##keytype##To##valuetype##EntryPointer;                           \
                                                                               \
  typedef valuetype (*Hashmap##keytype##To##valuetype##Function)(              \
      Hashmap##keytype##To##valuetype##Key, U64                                \
  );                                                                           \
  typedef B32 (*Hashmap##keytype##To##valuetype##NullElementFunction)(         \
      Hashmap##keytype##To##valuetype##EntryPointer                            \
  );                                                                           \
  typedef B32 (*Hashmap##keytype##To##valuetype##EqualElementFunction)(        \
      Hashmap##keytype##To##valuetype##EntryPointer,                           \
      Hashmap##keytype##To##valuetype##EntryPointer                            \
  );                                                                           \
                                                                               \
  typedef struct Hashmap##keytype##To##valuetype##                             \
  {                                                                            \
    U64 bucketcount;                                                           \
    U64 used_buckets;                                                          \
    U64 exponent;                                                              \
    Hashmap##keytype##To##valuetype##Entry* entries;                           \
    Hashmap##keytype##To##valuetype##Function hashfunction;                    \
    Hashmap##keytype##To##valuetype##NullElementFunction nullelemfunction;     \
    Hashmap##keytype##To##valuetype##EqualElementFunction equalelemfunction;   \
  } Hashmap##keytype##To##valuetype##;                                         \
                                                                               \
  void Hashmap##keytype##To##valuetype##Init(                                  \
      Arena* arena, Hashmap##keytype##To##valuetype##* hashmap, U64 exponent,  \
      Hashmap##keytype##To##valuetype##Function hashfunction,                  \
      Hashmap##keytype##To##valuetype##NullElementFunction nullelemfunction,   \
      Hashmap##keytype##To##valuetype##EqualElementFunction equalelemfunction  \
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
      Arena* arena, Hashmap##keytype##To##valuetype##* hashmap, U64 exponent,  \
      Hashmap##keytype##To##valuetype##Function hashfunction,                  \
      Hashmap##keytype##To##valuetype##NullElementFunction nullelemfunction,   \
      Hashmap##keytype##To##valuetype##EqualElementFunction equalelemfunction  \
  )                                                                            \
  {                                                                            \
    hashmap->exponent                           = exponent;                    \
    hashmap->bucketcount                        = 1 << exponent;               \
    hashmap->used_buckets                       = 0;                           \
    Hashmap##keytype##To##valuetype##Entry* mem = ArenaPush(                   \
        arena,                                                                 \
        hashmap->bucketcount * sizeof(Hashmap##keytype##To##valuetype##Entry)  \
    );                                                                         \
    hashmap->entries           = mem;                                          \
    hashmap->hashfunction      = hashfunction;                                 \
    hashmap->nullelemfunction  = nullelemfunction;                             \
    hashmap->equalelemfunction = equalelemfunction;                            \
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
                                                                               \
    U64 i = hash;                                                              \
    while (1)                                                                  \
    {                                                                          \
      i = __HashmapLookup(hash, hashmap->exponent, i);                         \
      if (hashmap->nullelemfunction(hashmap->entries + i))                     \
      {                                                                        \
        /* No more memory */                                                   \
        if ((U64)hashmap->used_buckets + 1 >= (U64)hashmap->bucketcount)       \
          return;                                                              \
                                                                               \
        hashmap->used_buckets += 1;                                            \
        *(hashmap->entries + i) = entry;                                       \
        return;                                                                \
      }                                                                        \
      /* return canonical instance if found one*/                              \
      else if (hashmap->equalelemfunction(&entry, hashmap->entries + i))       \
      {                                                                        \
        return;                                                                \
      }                                                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  Hashmap##keytype##To##valuetype##Value Hashmap##keytype##To##valuetype##Get( \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key                                 \
  )                                                                            \
  {                                                                            \
    Hashmap##keytype##To##valuetype##Entry entry = {0};                        \
    entry.key                                    = key;                        \
                                                                               \
    U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);               \
    U64 i    = hash;                                                           \
    while (1)                                                                  \
    {                                                                          \
      i = __HashmapLookup(hash, hashmap->exponent, i);                         \
      if (hashmap->nullelemfunction(hashmap->entries + i) ||                   \
          hashmap->equalelemfunction(&entry, hashmap->entries + i))            \
      {                                                                        \
        return (hashmap->entries + i)->value;                                  \
      }                                                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  B32 Hashmap##keytype##To##valuetype##TryGet(                                 \
      Hashmap##keytype##To##valuetype##* hashmap,                              \
      Hashmap##keytype##To##valuetype##Key key,                                \
      Hashmap##keytype##To##valuetype##Value* outvalue                         \
  )                                                                            \
  {                                                                            \
    Hashmap##keytype##To##valuetype##Entry entry = {0};                        \
    entry.key                                    = key;                        \
                                                                               \
    U64 hash = hashmap->hashfunction(key, hashmap->bucketcount);               \
    U64 i    = hash;                                                           \
    while (1)                                                                  \
    {                                                                          \
      i = __HashmapLookup(hash, hashmap->exponent, i);                         \
      if (hashmap->nullelemfunction(hashmap->entries + i))                     \
      {                                                                        \
        return 0;                                                              \
      }                                                                        \
      else if (hashmap->equalelemfunction(&entry, hashmap->entries + i))       \
      {                                                                        \
        *outvalue = (hashmap->entries + i)->value;                             \
        return 1;                                                              \
      }                                                                        \
    }                                                                          \
  }

#endif