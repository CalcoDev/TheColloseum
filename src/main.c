#include <stdio.h>

#include <stdlib.h>

#include "base/base_include.h"
#include "os/os.h"

int main()
{
  // Arena global_arena;
  // ArenaInit(&global_arena, Megabytes(1));

  // String8 a = Str8Lit("Samepl sample sample");
  // String8 b = Str8Lit("BBBBBBBB");

  // printf("a");

  // M_BaseMemory memory = M_MallocBaseMemory();
  M_BaseMemory memory = OS_BaseMemory();

  Arena arena;
  ArenaInit(&arena, &memory, Megabytes(1));

  String8 exe_path = OS_PathExecutableDir(&arena);
  String8 new_dir =
      OS_PathRelative(&arena, exe_path, Str8Lit("./ooga-booga-dir/sample.txt"));

  // B32 created_dir = OS_DirCreate(new_dir);
  // printf("Created Dir: %i\n", created_dir);

  OS_FileRename(&arena, new_dir, Str8Lit("aaaaaaa"));

  // B32 renamed_dir = OS_DirRename(&arena, new_dir, Str8Lit("ooga-booga-dir"));
  // printf("Renamed Dir: %i\n", renamed_dir);

  // String8 test = Str8LitArena(&arena, "Oooga booga lmao.");

  ArenaRelease(&arena);

  // U8* ptr = ArenaPush(&arena, 128);
  // for (U8 i = 0; i < 128; ++i)
  //   *(ptr + i) = i;

  // ArenaPopTo(&arena, 64);

  // TempArena temp = ArenaBeginTemp(&arena);

  // ptr = ArenaPush(&arena, 64);
  // for (U8 i = 0; i < 64; ++i)
  //   *(ptr + i) = 64 - i;

  // ArenaEndTemp(&temp);

  // String8 str =
  //     Str8LitArena(&arena, "First string allocated using Windows memory!");

  // printf("String: %s\n\n", (char*)str.data);

  // String8 cwd = OS_PathCurrentDir(&global_arena);
  // String8 relative_path = OS_PathRelative(&global_arena, cwd,
  // Str8Lit("../")); String8 exe_path =
  // OS_PathExecutableDir(&global_arena);

  // printf("CWD: %s\n\n", (char*)cwd.data);
  // printf("Relative path: %s\n\n", (char*)relative_path.data);
  // printf("Exe path: %s\n\n", (char*)exe_path.data);

  // String8 shader_path = OS_PathRelative(
  //     &global_arena, exe_path,
  //     Str8Lit("./assets/shaders/default_vert.vs")
  // );
  // String8 shader_content =
  //     OS_FileRead(&global_arena, (const char*)shader_path.data);

  // printf("Shader path: %s\n\n", (char*)shader_path.data);
  // printf("Shader content: %s\n\n", (char*)shader_content.data);

  // String8 random_path =
  //     OS_PathRelative(&global_arena, exe_path,
  //     Str8Lit("./new-pow.lore"));

  // OS_FileCreate((const char*)random_path.data);
  // U32 a = OS_FileDelete(random_path.data);
  // U32 b = OS_FileExists(random_path.data);
  // U32 c = OS_FileExists(cwd.data);
  // U32 d = OS_FileExists(
  //     OS_PathRelative(&global_arena, cwd, Str8Lit("./no-exist")).data
  // );

  // printf("a: %u\n", a);
  // printf("b: %u\n", b);
  // printf("c: %u\n", c);
  // printf("d: %u\n", d);

  // String8 user_data = OS_PathUserData(&global_arena);
  // String8 temp = OS_PathTempData(&global_arena);

  // printf("user data: %s\n", (char*)user_data.data);
  // printf("temp: %s\n", (char*)temp.data);

  // B32 wrote = OS_FileWrite(
  //     (const char*)random_path.data, Str8Lit("new lore. lore got revamped.")
  // );

  // if (wrote)
  //   printf("Wrote data to file.");
  // else
  //   printf("Failed writing data to file.");

  // char* path =
  // _fullpath(NULL, "..\\assets\\shaders\\default_vert.vs", _MAX_PATH);

  // char* a = getaShaderContent(path);
  // printf("Shader A:\n\n%s\n\n", a);

  // String8 contents = IO_ReadFileU8(&global_arena, path);
  // printf("Shader Mine:\n\n%s\n\n", (char*)contents.data);

  // Str8LitArena(
  //     &global_arena, "This is going to overwrite the previous things is it
  //     not?"
  // );

  // String8 str = Str8LitArena(&global_arena, "Random string");
  // printf("%s\n", str);

  // TempArena temp_arena = ArenaBeginTemp(&global_arena);
  // String8 str2 = Str8LitArena(&global_arena, "Temporary string?");
  // printf("%s\n", str2);

  // ArenaEndTemp(&temp_arena);
  // String8 str3 = Str8LitArena(&global_arena, "Overwrite temp string.");
  // printf("%s\n", str3);

  return 0;
}