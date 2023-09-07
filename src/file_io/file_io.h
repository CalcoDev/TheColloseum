#ifndef FILE_IO_H
#define FILE_IO_H

#include "base/base_memory.h"
#include "base/base_string.h"

String8 IO_ReadFileU8(Arena* arena, const char* filepath);

#endif