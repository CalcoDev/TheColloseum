#ifndef BASE_BITSET_H
#define BASE_BITSET_H

#include "base_math.h"
#include "base_memory.h"
#include "base_types.h"

typedef struct Bitset
{
  U8* data;
  U64 size;
} Bitset;

Bitset BitsetMake(U64 size, U8* data);
Bitset BitsetMakeSize(U64 size);
Bitset BitsetMakeArena(Arena* arena, U64 size, U8* data);
Bitset BitsetMakeArenaSize(Arena* arena, U64 size);

B32 BitsetIsBitInBounds(U64 byte_size, U64 bit);

B32 BitsetSet(Bitset* bitset, U64 bit);
B32 BitsetUnset(Bitset* bitset, U64 bit);
void BitsetReset(Bitset* bitset);

/**
 * @brief Get the bit at position bit.
 * @param bitset The bitset to check.
 * @param bit The position of the bit.
 * @warning Returns 0 if bit is out of bounds.
 * @return The value of the bit if it is in bounds, 0 otherwise.
 */
U8 BitsetGet(Bitset* bitset, U64 bit);

#endif