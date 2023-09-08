#include "os.h"

#include <Windows.h>
//
#include <Shlwapi.h>

// NOTE(calco): -- Basic Memory Allocator
// NOTE(calco): -- Windows implementation

// TODO(calco): Implement windows implementation.
void* m_os_win_reserve(void* ctx, U64 size) { return (malloc(size)); }
void m_os_win_commit(void* ctx, void* ptr, U64 size) {}
void m_os_win_decommit(void* ctx, void* ptr, U64 size) {}
void m_os_win_release(void* ctx, void* ptr, U64 size) { free(ptr); }
void m_os_win_copy(void* src, void* dest, U64 size) { memcpy(dest, src, size); }

M_BaseMemory OS_BaseMemory()
{
  static M_BaseMemory memory;
  if (memory.reserve == 0)
  {
    memory.reserve = m_os_win_reserve;
    memory.commit = m_os_win_commit;
    memory.decommit = m_os_win_decommit;
    memory.release = m_os_win_release;
    memory.copy = m_os_win_copy;
  }

  return memory;
}

// NOTE(calco): -- File I/O
B32 OS_FileCreate(const char* filepath) {}
B32 OS_FileDelete(const char* filepath) {}

B32 OS_FileExists(const char* filepath) {}
B32 OS_FileRename(const char* filepath) {}

String8 OS_FileRead(Arena* arena, const char* filepath) {}
B32 OS_FileWrite(const char* filepath, const char* data) {}

// NOTE(calco): -- Paths

// TODO(calco): Consider making this a string function.
String8 OS_PathCurrentDir(Arena* arena)
{
  U16 buffer[2048];

  // TODO(calco): This is technically a String16 not String8 but for now it work
  // TODO(calco): Inconsistent, as all other impls of this use A version.
  // TODO(calco): Look into fixing this.
  U64 size = (U64)GetCurrentDirectoryW(2048, buffer);
  String8 str = Str16ToStr8(arena, buffer, size);

  return Str8ReplaceChar(str, '\\', '/');
}

String8 OS_PathExecutableDir(Arena* arena)
{
  U16 buffer[2048];

  GetModuleFileNameA(NULL, buffer, 2048);
  U8* dir_ptr = strrchr(buffer, '\\');
  *(dir_ptr) = '\0';
  U64 size = strlen(buffer);
  String8 str = Str8InitArena(arena, buffer, size);

  Str8ReplaceChar(str, '\\', '/');

  return str;
}

String8 OS_PathUserData(Arena* arena) {}
String8 OS_PathTempData(Arena* arena) {}
String8 OS_PathRelative(Arena* arena, String8 base, String8 rel)
{
  U16 buffer[2048];

  // Windows-ify paths
  Str8ReplaceChar(base, '/', '\\');
  Str8ReplaceChar(rel, '/', '\\');

  // TODO(calco): String8 to String16
  PathCombineA(buffer, base.data, rel.data); // pathcombinew
  U64 combined_size = strlen(buffer);        // wslen
  // Str16ToStr8(arena, buffer, combined_size)
  String8 str = Str8InitArena(arena, buffer, combined_size);

  // Unwindows-ify paths
  Str8ReplaceChar(base, '\\', '/');
  Str8ReplaceChar(rel, '\\', '/');

  return Str8ReplaceChar(str, '\\', '/');
}