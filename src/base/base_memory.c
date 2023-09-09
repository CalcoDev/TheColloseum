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
  }

  return memory;
}

// NOTE(calco): -- Linear Allocator
void ArenaInit(Arena* arena, M_BaseMemory* memory, U64 size)
{
  arena->size = size;
  arena->memory = memory;

  void* mem = memory->reserve(memory->ctx, size);
  arena->start = mem;
  arena->push_offset = 0;
  arena->commit_offset = 0;
}

void* ArenaPush(Arena* arena, U64 size)
{
  void* res = 0;
  if ((arena->push_offset + size) <= arena->size)
  {
    // No overflow, can allocate
    res = arena->start + arena->push_offset;
    arena->push_offset += size;

    if (arena->push_offset > arena->commit_offset)
    {
      // Would overflow the committed area. Commit and align to something cuz
      // yes?
      U64 next_commit_pos = ClampTop(
          AlignUpPow2(arena->push_offset, Megabytes(64) - 1), arena->size
      );

      arena->memory->commit(
          arena->memory->ctx, arena->start + arena->commit_offset,
          next_commit_pos - arena->commit_offset
      );

      arena->commit_offset = next_commit_pos;
    }
  }

  return res;
}

void ArenaPopTo(Arena* arena, U64 pos)
{
  if (pos < arena->push_offset)
  {
    arena->push_offset = pos;

    // Decommit stuff. Could probably be refactored into own code.
    U64 next_commit_pos = ClampTop(
        AlignDownPow2(arena->push_offset, Megabytes(64) - 1), arena->size
    );

    if (next_commit_pos > 1 && next_commit_pos < arena->commit_offset)
    {
      arena->memory->decommit(
          arena->memory->ctx, arena->start + next_commit_pos,
          arena->commit_offset - next_commit_pos
      );

      arena->commit_offset = next_commit_pos;
    }
  }
}

// NOTE(calco): Deprecated for now
// void* ArenaAllocZero(Arena* arena, U64 size)
// {
//   void* res = ArenaPush(arena, size);
//   memset(res, 0, size);

//   return res;
// }

void ArenaRelease(Arena* arena)
{
  arena->memory->release(arena->memory->ctx, arena->start, arena->size);

  arena->size = 0;
  arena->memory = 0;
  arena->push_offset = 0;
  arena->commit_offset = 0;
}

TempArena ArenaBeginTemp(Arena* arena)
{
  TempArena temp;
  temp.arena = arena;

  temp.prev_push_offset = arena->push_offset;
  temp.prev_commit_offset = arena->commit_offset;

  return temp;
}

void ArenaEndTemp(TempArena* temp_arena)
{
  ArenaPopTo(temp_arena->arena, temp_arena->prev_push_offset);
}