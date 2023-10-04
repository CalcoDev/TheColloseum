#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include "base_types.h"

// NOTE(calco): -- Basic Memory Allocator
typedef void* M_ReserveFunc(void* ctx, U64 size);
typedef void M_CommitFunc(void* ctx, void* ptr, U64 size);
typedef void M_DecommitFunc(void* ctx, void* ptr, U64 size);
typedef void M_ReleaseFunc(void* ctx, void* ptr, U64 size);

typedef struct M_BaseMemory
{
  M_ReserveFunc* reserve;
  M_CommitFunc* commit;
  M_DecommitFunc* decommit;
  M_ReleaseFunc* release;
  void* ctx;
} M_BaseMemory;

M_BaseMemory M_MallocBaseMemory(void);

// NOTE(calco): -- Arena / Linear Allocator
typedef struct Arena
{
  M_BaseMemory* memory;
  U8* start;
  U64 push_offset;
  U64 commit_offset;
  U64 size;
} Arena;

void ArenaInit(Arena* arena, M_BaseMemory* memory, U64 size);

// TODO(calco): ArenaDealloc
// TODO(calco): align to pow of 2 byte.
void* ArenaPush(Arena* arena, U64 size);
void ArenaPopTo(Arena* arena, U64 pos);

// NOTE(calco): Deprecated for now
// void* ArenaAllocZero(Arena* arena, U64 size);

void ArenaRelease(Arena* arena);

/**
 * @brief Utility class for easily going back to a previous state of an Arena.
 */
typedef struct TempArena
{
  Arena* arena;
  U64 prev_push_offset;
  U64 prev_commit_offset;
} TempArena;

TempArena ArenaBeginTemp(Arena* arena);
void ArenaEndTemp(TempArena* temp_arena);

void ArenaEndTempSetZero(TempArena* temp_arena);

#endif