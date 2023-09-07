#include "base_memory.h"

#include <stdlib.h>

void* ArenaInit(Arena* arena, U64 size)
{
  U8* l = (U8*)malloc(size);

  for (int i = 0; i < 128; ++i)
    *(l + i) = i;

  arena->start = l;
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

void ArenaFree(Arena* arena)
{
  free(arena->start);

  arena->start = NULL;
  arena->current = NULL;
  arena->size = 0;
}