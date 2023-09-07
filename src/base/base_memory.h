#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include "base_types.h"

/// @brief Static linear allocator.
typedef struct Arena
{
  // Use U8 for byte level granularity.
  U8* start;
  U8* current;
  U64 size;
} Arena;

void* ArenaInit(Arena* arena, U64 size);
void* ArenaAlloc(Arena* arena, U64 size);
void ArenaFree(Arena* arena);

#endif