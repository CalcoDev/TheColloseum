#include "file_io.h"

#include <stdio.h>
#include <string.h>

#include "base/base_types.h"

String8 IO_ReadFileU8(Arena* arena, const char* filepath)
{
  // Open in binary to get length in bytes
  FILE* file = fopen(filepath, "rb");
  if (file == NULL)
  {
    // todo(calco): Failed to open file, do something.
    return Str8Lit("");
  }

  U8* buffer;
  U64 size;
  fseek(file, 0, SEEK_END);
  size = ftell(file);

  // Close and reopen file as text.
  fclose(file);
  file = fopen(filepath, "r");

  // TempArena temp_arena = ArenaBeginTemp(arena);
  buffer = ArenaAlloc(arena, size);
  fread((void*)buffer, sizeof(U8), size, file);
  return Str8Init(buffer, size);

  // ArenaEndTemp(&temp_arena);
  // return str;
}