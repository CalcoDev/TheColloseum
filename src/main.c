#include <stdio.h>

#include <stdlib.h>

#include "base/base_include.h"

int main()
{
  String8 str_stack = Str8Lit("Stack string");

  Arena global_arena;
  Arena string_arena;

  ArenaInit(&global_arena, Megabytes(1));
  String8 str_arena_global = Str8LitArena(&global_arena, "Global arena string");

  ArenaInitNested(&global_arena, &string_arena, Kilobytes(1));
  String8 str_arena_nest = Str8LitArena(&string_arena, "Nested arena string");

  printf("Nested arena scope.");
  printf("Global arena scope.");

  ArenaFree(&global_arena);
  printf("Stack scope.");
  return 0;
}