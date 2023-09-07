#include "file_io.h"

#include <stdio.h>
#include <string.h>

#include "base/base_types.h"

/*

  FILE* fp;
  long size = 0;
  char* shaderContent;

  fp = fopen(fileName, "rb");
  if (fp == NULL)
  {
    return "";
  }
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp) + 1;
  fclose(fp);

  fp = fopen(fileName, "r");
  shaderContent = memset(malloc(size), '\0', size);
  fread(shaderContent, 1, size - 1, fp);
  fclose(fp);

  return shaderContent;


*/

// NOTE(calco): General impl doesn't work. Must do operating system style.
String8 IO_ReadFileU8(Arena* arena, const char* filepath)
{
  // Open in binary to get length in bytes
  FILE* file = fopen(filepath, "rb");
  if (file == NULL)
  {
    // todo(calco): Failed to open file, do something.
    // todo(calco): This function can now return both in stack and memory arena
    // values. might be worth ... not doing this
    return Str8LitArena(arena, "");
  }

  U64 size;
  fseek(file, 0L, SEEK_END);

  // Gets the wrong size. Worked previously because we were appending extra '\0'
  // Should be done per os.sa
  size = ftell(file);
  fclose(file);

  // Close and reopen file as text.
  file = fopen(filepath, "r");
  // todo(calco): Figure out if operation failed and stuff.
  // TempArena temp_arena = ArenaBeginTemp(arena);

  String8 str = Str8InitArenaSize(arena, size);
  fread(str.data, sizeof(U8), size, file);
  fclose(file);

  return str;
}