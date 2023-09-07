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
void* ArenaInitNested(Arena* parent, Arena* child, U64 size);

// TODO(calco): align to pow of 2 byte.
void* ArenaAlloc(Arena* arena, U64 size);
void* ArenaAllocZero(Arena* arena, U64 size);

void ArenaFree(Arena* arena);

typedef struct TempArena
{
  U8* prev_offset;
  U8* curr_offset;
  Arena* arena;
} TempArena;

TempArena ArenaBeginTemp(Arena* arena);
void ArenaEndTemp(TempArena* temp_arena);

#endif