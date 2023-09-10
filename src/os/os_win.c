#include "os.h"

#include <Shlwapi.h>
#include <UserEnv.h>
#include <Windows.h>

// NOTE(calco): -- Initialization --
static U64 WIN32_TICKS_PER_SECOND;

void OS_Init()
{
  LARGE_INTEGER perf_freq = {0};
  if (QueryPerformanceFrequency(&perf_freq))
  {
    WIN32_TICKS_PER_SECOND =
        ((U64)perf_freq.HighPart << 32) | perf_freq.LowPart;
  }
  timeBeginPeriod(1);
}

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
    memory.reserve  = m_os_win_reserve;
    memory.commit   = m_os_win_commit;
    memory.decommit = m_os_win_decommit;
    memory.release  = m_os_win_release;
  }

  return memory;
}

// NOTE(calco): -- File I/O
B32 OS_DirCreate(String8 filepath)
{
  return CreateDirectoryA(filepath.data, NULL);
}

B32 OS_DirDelete(String8 filepath) { return RemoveDirectoryA(filepath.data); }

B32 OS_DirRename(Arena* arena, String8 filepath, String8 name)
{
  TempArena tmp = ArenaBeginTemp(arena);

  String8 backpath = Str8LitArena(arena, "../");
  String8 s        = Str8InitArenaSize(arena, name.size + backpath.size);
  memcpy(s.data, backpath.data, backpath.size);
  memcpy((s.data + backpath.size), name.data, name.size);

  String8 new_filepath = OS_PathRelative(arena, filepath, s);
  B32 success          = MoveFileA(filepath.data, new_filepath.data);

  ArenaEndTemp(&tmp);

  return success;
}

B32 OS_FileCreate(String8 filepath)
{
  HANDLE file = CreateFileA(
      filepath.data,         //
      GENERIC_WRITE,         //
      0,                     //
      NULL,                  //
      CREATE_NEW,            //
      FILE_ATTRIBUTE_NORMAL, //
      NULL                   //
  );

  return (B32)(file == INVALID_HANDLE_VALUE);
}
B32 OS_FileDelete(String8 filepath) { return DeleteFileA(filepath.data); }

U32 OS_FileExists(String8 filepath)
{
  U32 file_attrib = GetFileAttributesA(filepath.data);

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

B32 OS_FileRename(Arena* arena, String8 filepath, String8 name)
{
  TempArena tmp = ArenaBeginTemp(arena);

  String8 backpath = Str8LitArena(arena, "../");
  String8 s        = Str8InitArenaSize(arena, name.size + backpath.size);
  memcpy(s.data, backpath.data, backpath.size);
  memcpy((s.data + backpath.size), name.data, name.size);

  String8 new_filepath = OS_PathRelative(arena, filepath, s);
  B32 success          = MoveFileA(filepath.data, new_filepath.data);

  ArenaEndTemp(&tmp);

  return success;
}

// TODO(calco): NO ERROR HANDLING
/**
 * @brief Reads the contents of a file.
 * @param arena The arena used for allocating the return buffer.
 * @param filepath The path to the file to be read.
 * @return The contents of the file, in an 8-bit string.
 */
String8 OS_FileRead(Arena* arena, String8 filepath)
{
  // Open file
  HANDLE file = CreateFileA(
      filepath.data, // path to file
      GENERIC_READ,  // access rights
      0,    // share stuff with os. 0 means nothing can read write and delete
      NULL, // some security things and stuff aaa
      OPEN_EXISTING,         // behaviour for stuff
      FILE_ATTRIBUTE_NORMAL, // Default file stuff
      NULL
  );

  // Get file size in bytes
  U64 size    = (U64)GetFileSize(file, NULL);
  String8 str = Str8InitArenaSize(arena, size);

  U32 bytes_read = 0;
  B32 success    = ReadFile(file, str.data, size, &bytes_read, NULL);

  CloseHandle(file);

  if (success)
    return str;
  else
    return Str8Lit("");
}

B32 OS_FileWrite(String8 filepath, String8 string)
{
  // Open file
  HANDLE file = CreateFileA(
      filepath.data, // path to file
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
  U64 size    = (U64)GetCurrentDirectoryW(2048, buffer);
  String8 str = Str16ToStr8(arena, buffer, size);

  return Str8ReplaceChar(str, '\\', '/');
}

String8 OS_PathExecutableDir(Arena* arena)
{
  U16 buffer[2048];

  GetModuleFileNameA(NULL, buffer, 2048);
  U8* dir_ptr = strrchr(buffer, '\\');
  *(dir_ptr)  = '\0';
  U64 size    = strlen(buffer);
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
  U64 size    = strlen(buffer);
  String8 str = Str8InitArena(arena, buffer, size);

  // Dewindowsify paths
  return Str8ReplaceChar(str, '\\', '/');
}

String8 OS_PathTempData(Arena* arena)
{
  U8 buffer[2048];
  B32 success = GetTempPathA(2048, buffer);
  // TODO(calco): Error handling
  U64 size    = strlen(buffer);
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

// NOTE(calco): -- Time --

// DateTime OS_TimeSystemTimeToDateTime(SYSTEM);
// os_specific_time OS_TimeDateTimeToSystemTime(DateTime date_time);

DateTime conv_SystemTimeToDateTime(SYSTEMTIME system_time)
{
  DateTime time   = {0};
  time.milisecond = system_time.wMilliseconds;
  time.second     = system_time.wSecond;
  time.minute     = system_time.wMinute;
  time.hour       = system_time.wHour;
  time.day        = system_time.wDay;
  time.month      = system_time.wMonth;
  time.year       = system_time.wYear;
  return time;
}

SYSTEMTIME conv_DateTimeToSystemTime(DateTime date_time)
{
  SYSTEMTIME system_time    = {0};
  system_time.wMilliseconds = date_time.milisecond;
  system_time.wSecond       = date_time.second;
  system_time.wMinute       = date_time.minute;
  system_time.wHour         = date_time.hour;
  system_time.wDay          = date_time.day;
  system_time.wMonth        = date_time.month;
  system_time.wYear         = date_time.year;
  return system_time;
}

DateTime OS_TimeUniversal()
{
  SYSTEMTIME system_time;
  GetSystemTime(&system_time);
  return conv_SystemTimeToDateTime(system_time);
}

DateTime OS_TimeLocal()
{
  SYSTEMTIME universal_time;
  SYSTEMTIME local_time;
  GetSystemTime(&universal_time);
  SystemTimeToTzSpecificLocalTime(NULL, &universal_time, &local_time);
  return conv_SystemTimeToDateTime(local_time);
}

DateTime OS_TimeLocalFromUniversal(DateTime universal)
{
  SYSTEMTIME universal_time = conv_DateTimeToSystemTime(universal);
  SYSTEMTIME local_time;
  GetSystemTime(&universal_time);
  SystemTimeToTzSpecificLocalTime(NULL, &universal_time, &local_time);
  return conv_SystemTimeToDateTime(local_time);
}

DateTime OS_TimeUniversalFromLocal(DateTime local)
{
  SYSTEMTIME local_time = conv_DateTimeToSystemTime(local);
  SYSTEMTIME universal_time;
  TzSpecificLocalTimeToSystemTime(NULL, &local_time, &universal_time);
  return conv_SystemTimeToDateTime(universal_time);
}

PrecisionTime OS_TimeMicroseconds()
{
  U64 result                 = 0;
  LARGE_INTEGER perf_counter = {0};
  if (QueryPerformanceCounter(&perf_counter))
  {
    U64 ticks = ((U64)perf_counter.HighPart << 32) | perf_counter.LowPart;
    result    = ticks * 1000000 / WIN32_TICKS_PER_SECOND;
  }
  return (PrecisionTime)result;
}