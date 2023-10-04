#include "base_hashmap.h"

U64 __HashmapLookup(U64 hash, S32 exp, S32 idx)
{
  U32 mask = ((uint32_t)1 << exp) - 1;
  U32 step = (hash >> (64 - exp)) | 1;
  return (idx + step) & mask;
}