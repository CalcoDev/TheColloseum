#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include "base_types.h"

// NOTE(calco): -- Basic Memory Allocator
typedef void* M_ReserveFunc(void* ctx, U64 size);
typedef void M_CommitFunc(void* ctx, void* ptr, U64 size);
typedef void M_DecommitFunc(void* ctx, void* ptr, U64 size);
typedef void M_ReleaseFunc(void* ctx, void* ptr, U64 size);

typedef void M_CopyFunc(void* src, void* dest, U64 size);

typedef struct M_BaseMemory
{
  M_ReserveFunc* reserve;
  M_CommitFunc* commit;
  M_DecommitFunc* decommit;
  M_ReleaseFunc* release;
  M_CopyFunc* copy;
  void* ctx;
} M_BaseMemory;

M_BaseMemory M_MallocBaseMemory(void);

// NOTE(calco): -- Arena / Linear Allocator
typedef struct Arena
{
  U8* start;
  U8* current;
  U64 size;
} Arena;

void* ArenaInit(Arena* arena, U64 size);
void* ArenaInitNested(Arena* parent, Arena* child, U64 size);

// TODO(calco): ArenaDealloc
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