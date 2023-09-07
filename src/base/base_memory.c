#include "base_memory.h"

#include <stdlib.h>
#include <string.h>

void* ArenaInit(Arena* arena, U64 size)
{
  arena->start = (U8*)malloc(size);
  arena->current = arena->start;
  arena->size = size;
}

void* ArenaAlloc(Arena* arena, U64 size)
{
  B8 overflow = (arena->current + size) > (arena->start + arena->size);
  if (!overflow)
  {
    U8* mem = arena->current;
    arena->current = arena->current + size;

    return mem;
  }
  else
  {
    // todo(calco): Assert or something.
    return NULL;
  }
}

void* ArenaAllocZero(Arena* arena, U64 size)
{
  void* res = ArenaAlloc(arena, size);
  memset(res, 0, size);

  return res;
}

void ArenaFree(Arena* arena)
{
  free(arena->start);

  arena->start = NULL;
  arena->current = NULL;
  arena->size = 0;
}