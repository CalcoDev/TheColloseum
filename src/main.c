#include <stdio.h>

#include <stdlib.h>

#include "base/base_include.h"

int main()
{
  Arena arena;
  ArenaInit(&arena, Kilobytes(2));

  U8* array = (U8*)ArenaAlloc(&arena, Kilobytes(1));
  for (int i = 0; i < 128; ++i)
    *(array + i) = i;

  ArenaFree(&arena);
  return 0;
}