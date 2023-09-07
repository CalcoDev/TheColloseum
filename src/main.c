#include <stdio.h>

#include <stdlib.h>

#include "base/base_include.h"
#include "file_io/file_io.h"

int main()
{
  Arena global_arena;
  ArenaInit(&global_arena, Megabytes(1));

  char* path =
      _fullpath(NULL, "..\\assets\\shaders\\default_vert.vs", _MAX_PATH);

  String8 contents = IO_ReadFileU8(&global_arena, path);
  printf("Shader:\n\n%s\n\n", contents.data);

  Str8LitArena(
      &global_arena, "This is going to overwrite the previous things is it not?"
  );

  // String8 str = Str8LitArena(&global_arena, "Random string");
  // printf("%s\n", str);

  // TempArena temp_arena = ArenaBeginTemp(&global_arena);
  // String8 str2 = Str8LitArena(&global_arena, "Temporary string?");
  // printf("%s\n", str2);

  // ArenaEndTemp(&temp_arena);
  // String8 str3 = Str8LitArena(&global_arena, "Overwrite temp string.");
  // printf("%s\n", str3);

  ArenaFree(&global_arena);
  return 0;
}