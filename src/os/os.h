#ifndef OS_H
#define OS_H

#include "base/base_context.h"
#include "base/base_memory.h"

#include "base/base_string.h"

// NOTE(calco): -- Memory
M_BaseMemory OS_BaseMemory();

// NOTE(calco): -- File I/O

// ?? TODO(calco): Use basic char* or string
B32 OS_FileCreate(const char* filepath);
B32 OS_FileDelete(const char* filepath);

B32 OS_FileExists(const char* filepath);
B32 OS_FileRename(const char* filepath, const char* name);

String8 OS_FileRead(Arena* arena, const char* filepath);
B32 OS_FileWrite(const char* filepath, const char* data);

// NOTE(calco): -- Paths
String8 OS_PathCurrentDir(Arena* arena);
String8 OS_PathUserData(Arena* arena);
String8 OS_PathTempData(Arena* arena);
String8 OS_PathAbolsute(const char* relative);

#endif