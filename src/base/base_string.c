#include "base_string.h"

#include <string.h>

String8 Str8Init(U8* data, U64 size)
{
  String8 str;
  str.data = data;
  str.size = size;
  return str;
}

String8 Str8InitArenaSize(Arena* arena, U64 size)
{
  U8* ptr = (U8*)ArenaAlloc(arena, size + 1);
  ptr[size] = '\0';
  return Str8Init(ptr, size);
}

String8 Str8InitArena(Arena* arena, U8* data, U64 size)
{
  String8 str = Str8InitArenaSize(arena, size);
  memcpy(str.data, data, size);
  return str;
}

U8* Str8CString(String8 string)
{
  // Should do some checks to see if it is null terminated
  return string.data;
}

String8 Str8Prefix(String8 string, U64 size)
{
  string.size += size;
  string.data -= size;

  return string;
}

String8 Str8Postfix(String8 string, U64 size)
{
  string.size += size;
  return string;
}