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
  U8* ptr   = (U8*)ArenaPush(arena, size + 1);
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

/**
 * @brief Converts a string with 16-bit wide character to 8-bit wide.
 *
 * @warning Scuffed because I am not actually converting UTF16 to UTF8 or ASCII
 * But just chopping off 8 bits from the end.
 *
 * @param arena A memory arena used for allocating the new buffer.
 * @param buffer The 16-bit wide character buffer.
 * @param size The number of characters in the 16-bit wide character buffer.
 * @return String8
 */
String8 Str16ToStr8(Arena* arena, U16* buffer, U64 size)
{
  String8 str = Str8InitArenaSize(arena, size);

  U16* ptr_16 = buffer;
  U8* ptr_8   = str.data;

  U16* limit = (buffer + size);
  while (ptr_16 < limit)
  {
    U16 val = (*ptr_16);
    U8 low  = val & 0xFF;
    U8 high = (val >> 8) & 0xFF;

    *(ptr_8) = low;

    ptr_8 += 1;
    ptr_16 += 1;
  }

  return str;
}

// Helper Functions
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

String8 Str8ReplaceChar(String8 string, const U8 prev, const U8 current)
{
  U8* ptr   = string.data;
  U8* limit = string.data + string.size;
  while (ptr < limit)
  {
    if (*(ptr) == prev)
      *(ptr) = current;

    ptr += 1;
  }

  return string;
}