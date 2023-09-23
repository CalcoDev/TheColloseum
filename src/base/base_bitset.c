#include "base_bitset.h"

#include <string.h>

Bitset BitsetMake(U64 size, U8* data)
{
  Bitset bitset;
  bitset.size = size;
  bitset.data = data;
  return bitset;
}

Bitset BitsetMakeSize(U64 size)
{
  Bitset bitset;
  bitset.size = size;
  bitset.data = NULL;
  return bitset;
}

Bitset BitsetMakeArena(Arena* arena, U64 size, U8* data)
{
  Bitset bitset = BitsetMakeArenaSize(arena, size);
  memcpy(bitset.data, data, size);
  return bitset;
}

Bitset BitsetMakeArenaSize(Arena* arena, U64 size)
{
  Bitset bitset;
  bitset.size = size;
  bitset.data = (U8*)ArenaPush(arena, DivCeil(size, 8));
  return bitset;
}

B32 BitsetIsBitInBounds(U64 byte_size, U64 bit)
{
  U64 idx       = DivFloor(bit, 8);
  U64 remainder = bit - idx * 8;

  return !(idx > byte_size - 1 || (idx == byte_size - 1 && remainder > 0));
}

B32 bitset_TrySetBit(Bitset* bitset, U64 bit, B32 set)
{
  U64 idx       = DivFloor(bit, 8);
  U64 remainder = bit - idx * 8;

  if (bit >= bitset->size)
    return 0;

  if (set)
    bitset->data[idx] |= (1UL << remainder);
  else
    bitset->data[idx] &= ~(1UL << remainder);

  return 1;
}

B32 BitsetSet(Bitset* bitset, U64 bit)
{
  return bitset_TrySetBit(bitset, bit, 1);
}

B32 BitsetUnset(Bitset* bitset, U64 bit)
{
  return bitset_TrySetBit(bitset, bit, 0);
}

void BitsetReset(Bitset* bitset)
{
  for (U64 i = 0; i < bitset->size; ++i)
    bitset->data[i] = 0;
}

U8 BitsetGet(Bitset* bitset, U64 bit)
{
  U64 idx       = DivFloor(bit, 8);
  U64 remainder = bit - idx * 8;

  if (bit >= bitset->size)
    return 0;

  U8* byte = &(bitset->data[idx]);
  return ((*byte >> remainder) & 0x01);
}