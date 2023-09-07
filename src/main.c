#include <stdio.h>

#include <stdlib.h>

#include "base/base_include.h"

int main()
{
  Arena arena;
  ArenaInit(&arena, Megabytes(1));

  StringU8 sample = Str8Lit("Help please");
  StringU8 arena_string = Str8InitArena(&arena, Str8Expand(sample));
  StringU8 arena_str = Str8LitArena(&arena, "Welcome to the arena!");

  ArenaFree(&arena);
  return 0;
}