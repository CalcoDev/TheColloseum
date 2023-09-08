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

/**
 * @brief Checks whether a file or directory exists.
 * @param filepath The path to check.
 * @return 0, if the file doesn't exist, 1 if it is a file, 2 if it is a
 * directory.
 */
S32 OS_FileExists(const char* filepath);
B32 OS_FileRename(const char* filepath, const char* name);

String8 OS_FileRead(Arena* arena, const char* filepath);
B32 OS_FileWrite(const char* filepath, String8 string);

// NOTE(calco): -- Paths
String8 OS_PathCurrentDir(Arena* arena);
String8 OS_PathExecutableDir(Arena* arena);
String8 OS_PathUserData(Arena* arena);
String8 OS_PathTempData(Arena* arena);
String8 OS_PathRelative(Arena* arena, String8 base, String8 rel);

#endif