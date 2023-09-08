#include "os.h"

#include <Shlwapi.h>
#include <UserEnv.h>
#include <Windows.h>

// NOTE(calco): -- Basic Memory Allocator
// NOTE(calco): -- Windows implementation

// TODO(calco): Implement windows implementation.
void* m_os_win_reserve(void* ctx, U64 size)
{
  return VirtualAlloc(
      NULL,         // Tells win to allocate it wherever
      size,         //
      MEM_RESERVE,  // Just reserve the memory
      PAGE_NOACCESS // Read or write => access violation error
  );
}

void m_os_win_commit(void* ctx, void* ptr, U64 size)
{
  return VirtualAlloc(
      ptr,           // Tells win to allocate it in the reserved memory
      size,          //
      MEM_COMMIT,    // Just commit
      PAGE_READWRITE // Read or write
  );
}

void m_os_win_decommit(void* ctx, void* ptr, U64 size)
{
  VirtualFree(ptr, size, MEM_DECOMMIT);
}

void m_os_win_release(void* ctx, void* ptr, U64 size)
{
  VirtualFree(ptr, 0, MEM_RELEASE);
}

M_BaseMemory OS_BaseMemory()
{
  static M_BaseMemory memory;
  if (memory.reserve == 0)
  {
    memory.reserve = m_os_win_reserve;
    memory.commit = m_os_win_commit;
    memory.decommit = m_os_win_decommit;
    memory.release = m_os_win_release;
  }

  return memory;
}

// NOTE(calco): -- File I/O
B32 OS_FileCreate(const char* filepath)
{
  HANDLE file = CreateFileA(
      filepath,              //
      GENERIC_WRITE,         //
      0,                     //
      NULL,                  //
      CREATE_NEW,            //
      FILE_ATTRIBUTE_NORMAL, //
      NULL                   //
  );

  return (B32)(file == INVALID_HANDLE_VALUE);
}
B32 OS_FileDelete(const char* filepath) { return (B32)DeleteFile(filepath); }

U32 OS_FileExists(const char* filepath)
{
  U32 file_attrib = GetFileAttributesA(filepath);

  //  TODO(calco): Maybe this doesnt cover quite all cases.
  if (file_attrib == INVALID_FILE_ATTRIBUTES &&
      GetLastError() == ERROR_FILE_NOT_FOUND)
  {
    return 0;
  }

  if (file_attrib && FILE_ATTRIBUTE_DIRECTORY)
    return 2;

  return 1;
}

B32 OS_FileRename(const char* filepath, const char* name) {}

// TODO(calco): NO ERROR HANDLING
/**
 * @brief Reads the contents of a file.
 * @param arena The arena used for allocating the return buffer.
 * @param filepath The path to the file to be read.
 * @return The contents of the file, in an 8-bit string.
 */
String8 OS_FileRead(Arena* arena, const char* filepath)
{
  // Open file
  HANDLE file = CreateFileA(
      filepath,     // path to file
      GENERIC_READ, // access rights
      0,    // share stuff with os. 0 means nothing can read write and delete
      NULL, // some security things and stuff aaa
      OPEN_EXISTING,         // behaviour for stuff
      FILE_ATTRIBUTE_NORMAL, // Default file stuff
      NULL
  );

  // Get file size in bytes
  U64 size = (U64)GetFileSize(file, NULL);
  String8 str = Str8InitArenaSize(arena, size);

  U32 bytes_read = 0;
  B32 success = ReadFile(file, str.data, size, &bytes_read, NULL);

  CloseHandle(file);

  if (success)
    return str;
  else
    return Str8Lit("");
}

B32 OS_FileWrite(const char* filepath, String8 string)
{
  // Open file
  HANDLE file = CreateFileA(
      filepath,      // path to file
      GENERIC_WRITE, // access rights
      0,    // share stuff with os. 0 means nothing can read write and delete
      NULL, // some security things and stuff aaa
      OPEN_ALWAYS,           // behaviour for stuff
      FILE_ATTRIBUTE_NORMAL, // Default file stuff
      NULL
  );

  U32 bytes_written = 0;
  B32 success = WriteFile(file, string.data, string.size, &bytes_written, NULL);

  CloseHandle(file);

  return success;
}

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

String8 OS_PathUserData(Arena* arena)
{
  U8 buffer[2048];
  // HANDLE token = GetCurrentProcessToken();

  HANDLE token;
  B32 s_token = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token);

  U32 l_userdata = 2048;
  B32 s_userdata = GetUserProfileDirectoryA(token, buffer, &l_userdata);
  // TODO(calco): Error handling
  U64 size = strlen(buffer);
  String8 str = Str8InitArena(arena, buffer, size);

  // Dewindowsify paths
  return Str8ReplaceChar(str, '\\', '/');
}

String8 OS_PathTempData(Arena* arena)
{
  U8 buffer[2048];
  B32 success = GetTempPathA(2048, buffer);
  // TODO(calco): Error handling
  U64 size = strlen(buffer);
  String8 str = Str8InitArena(arena, buffer, size);

  return Str8ReplaceChar(str, '\\', '/');
}

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