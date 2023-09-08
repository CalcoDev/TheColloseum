#include "base_memory.h"

#include <stdlib.h>
#include <string.h>

// NOTE(calco): -- Basic Memory Allocator
// NOTE(calco): -- Malloc & Free implementation
void* m_malloc_reserve(void* ctx, U64 size) { return (malloc(size)); }
void m_malloc_commit(void* ctx, void* ptr, U64 size) {}
void m_malloc_decommit(void* ctx, void* ptr, U64 size) {}
void m_malloc_release(void* ctx, void* ptr, U64 size) { free(ptr); }
void m_malloc_copy(void* src, void* dest, U64 size) { memcpy(dest, src, size); }

M_BaseMemory M_MallocBaseMemory(void)
{
  static M_BaseMemory memory;
  if (memory.reserve == 0)
  {
    memory.reserve = m_malloc_reserve;
    memory.commit = m_malloc_commit;
    memory.decommit = m_malloc_decommit;
    memory.release = m_malloc_release;
    memory.copy = m_malloc_copy;
  }

  return memory;
}

// NOTE(calco): -- Linear Allocator
void* init_arena_mem(Arena* arena, void* mem, U64 size)
{
  arena->start = mem;
  arena->current = mem;
  arena->size = size;

  return mem;
}

void* ArenaInit(Arena* arena, U64 size)
{
  return init_arena_mem(arena, malloc(size), size);
}

void* ArenaInitNested(Arena* parent, Arena* child, U64 size)
{
  return init_arena_mem(child, ArenaAlloc(parent, size), size);
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

TempArena ArenaBeginTemp(Arena* arena)
{
  TempArena temp;
  temp.curr_offset = arena->current;
  temp.prev_offset = arena->current;
  temp.arena = arena;

  return temp;
}

void ArenaEndTemp(TempArena* temp_arena)
{
  temp_arena->arena->current = temp_arena->prev_offset;
}