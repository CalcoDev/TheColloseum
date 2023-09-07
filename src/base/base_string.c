#include "base_string.h"

StringU8 Str8Init(U8* data, U64 size)
{
  StringU8 str;
  str.data = data;
  str.size = size;
  return str;
}

U8* Str8CString(StringU8 string)
{
  // Should do some checks to see if it is null terminated
  return string.data;
}

StringU8 Str8Prefix(StringU8 string, U64 size)
{
  string.size += size;
  string.data -= size;

  return string;
}

StringU8 Str8Postfix(StringU8 string, U64 size)
{
  string.size += size;
  return string;
}