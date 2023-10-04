#include <glad/glad.h>
// seaprate so that glad is always first
#include <glfw/glfw3.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "base/base_include.h"
#include "os/os.h"

#define OS_WINDOW_MAX_KEY_CALLBACK_SIZE            2
#define OS_WINDOW_MAX_MOUSE_BUTTON_CALLBACK_SIZE   2
#define OS_WINDOW_MAX_MOUSE_POSITION_CALLBACK_SIZE 2
#include "os/os_window.h"

#include "render/camera/render_camera.h"
#include "render/render.h"

#include "os/input/os_input.h"

#include "input/input.h"

U64 str_hash_t(CharPointer key, U64 table_size)
{
  uint64_t h  = 0x100;
  int32_t len = strlen(key);
  for (int32_t i = 0; i < len; i++)
  {
    h ^= key[i] & 255;
    h *= 1111111111111111111;
  }
  return h ^ h >> 32;
}

B32 str_null_t(HashmapEntryPointer(CharPointer, U8) entry)
{
  if (entry->key == '\0' || strlen(entry->key) == 0)
    return 1;

  return 0;
}

B32 str_elem_eq(
    HashmapEntryPointer(CharPointer, U8) e1,
    HashmapEntryPointer(CharPointer, U8) e2
)
{
  B32 both_null = (e1->key == '\0' && e2->key == '\0');
  B32 one_null  = (e1->key == '\0' && e2->key != '\0') ||
                 (e2->key == '\0' && e1->key != '\0');

  if (both_null)
    return 1;
  if (one_null)
    return 0;

  return strcmp(e1->key, e2->key) == 0;
}

#define EXP 9

int main()
{
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Gigabytes(1));

  Hashmap(CharPointer, U8) map;
  HashmapInit(
      CharPointer, U8, &arena, &map, 9, str_hash_t, str_null_t, str_elem_eq
  );

  HashmapAdd(CharPointer, U8, &map, "sample", 12);
  Log("Added something to hashmap.", "");

  U8 e = HashmapGet(CharPointer, U8, &map, "sample");
  Log("Got value from hashmap: %u", e);

  U8 e1 = HashmapGet(CharPointer, U8, &map, "nonexistent");
  Log("Nonexistent value what go on: %u", e1);

  if (HashmapTryGet(CharPointer, U8, &map, "sample", &e))
    Log("Found e: %u", e);
  else
    Log("Couldn't find e.", "");

  if (HashmapTryGet(CharPointer, U8, &map, "noexist", &e1))
    Log("Found e: %u", e1);
  else
    Log("Couldn't find e1.", "");

  ArenaRelease(&arena);
}

int ___main()
{
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Gigabytes(1));

  Hashmap(CharPointer, U8) key_mapper;
  // INITIALIZING ALL ELEMENTS
  {
    HashmapInit(
        CharPointer, U8, &arena, &key_mapper, 9, str_hash_t, str_null_t,
        str_elem_eq
    );

    HashmapAdd(
        CharPointer, U8, &key_mapper, "MouseLeft", OS_Input_MouseButton_Left
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "MouseMiddle", OS_Input_MouseButton_Middle
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "MouseRight", OS_Input_MouseButton_Right
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "LeftArrow", OS_Input_KeyLeftArrow
    );
    HashmapAdd(CharPointer, U8, &key_mapper, "UpArrow", OS_Input_KeyUpArrow);
    HashmapAdd(
        CharPointer, U8, &key_mapper, "RightArrow", OS_Input_KeyRightArrow
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "DownArrow", OS_Input_KeyDownArrow
    );
    HashmapAdd(CharPointer, U8, &key_mapper, "Minus", OS_Input_KeyMinus);
    HashmapAdd(CharPointer, U8, &key_mapper, "Equals", OS_Input_KeyEquals);
    HashmapAdd(
        CharPointer, U8, &key_mapper, "Backspace", OS_Input_KeyBackspace
    );
    HashmapAdd(CharPointer, U8, &key_mapper, "0", OS_Input_Key0);
    HashmapAdd(CharPointer, U8, &key_mapper, "1", OS_Input_Key1);
    HashmapAdd(CharPointer, U8, &key_mapper, "2", OS_Input_Key2);
    HashmapAdd(CharPointer, U8, &key_mapper, "3", OS_Input_Key3);
    HashmapAdd(CharPointer, U8, &key_mapper, "4", OS_Input_Key4);
    HashmapAdd(CharPointer, U8, &key_mapper, "5", OS_Input_Key5);
    HashmapAdd(CharPointer, U8, &key_mapper, "6", OS_Input_Key6);
    HashmapAdd(CharPointer, U8, &key_mapper, "7", OS_Input_Key7);
    HashmapAdd(CharPointer, U8, &key_mapper, "8", OS_Input_Key8);
    HashmapAdd(CharPointer, U8, &key_mapper, "9", OS_Input_Key9);
    HashmapAdd(CharPointer, U8, &key_mapper, "A", OS_Input_KeyA);
    HashmapAdd(CharPointer, U8, &key_mapper, "B", OS_Input_KeyB);
    HashmapAdd(CharPointer, U8, &key_mapper, "C", OS_Input_KeyC);
    HashmapAdd(CharPointer, U8, &key_mapper, "D", OS_Input_KeyD);
    HashmapAdd(CharPointer, U8, &key_mapper, "E", OS_Input_KeyE);
    HashmapAdd(CharPointer, U8, &key_mapper, "F", OS_Input_KeyF);
    HashmapAdd(CharPointer, U8, &key_mapper, "G", OS_Input_KeyG);
    HashmapAdd(CharPointer, U8, &key_mapper, "H", OS_Input_KeyH);
    HashmapAdd(CharPointer, U8, &key_mapper, "I", OS_Input_KeyI);
    HashmapAdd(CharPointer, U8, &key_mapper, "J", OS_Input_KeyJ);
    HashmapAdd(CharPointer, U8, &key_mapper, "K", OS_Input_KeyK);
    HashmapAdd(CharPointer, U8, &key_mapper, "L", OS_Input_KeyL);
    HashmapAdd(CharPointer, U8, &key_mapper, "M", OS_Input_KeyM);
    HashmapAdd(CharPointer, U8, &key_mapper, "N", OS_Input_KeyN);
    HashmapAdd(CharPointer, U8, &key_mapper, "O", OS_Input_KeyO);
    HashmapAdd(CharPointer, U8, &key_mapper, "P", OS_Input_KeyP);
    HashmapAdd(CharPointer, U8, &key_mapper, "Q", OS_Input_KeyQ);
    HashmapAdd(CharPointer, U8, &key_mapper, "R", OS_Input_KeyR);
    HashmapAdd(CharPointer, U8, &key_mapper, "S", OS_Input_KeyS);
    HashmapAdd(CharPointer, U8, &key_mapper, "T", OS_Input_KeyT);
    HashmapAdd(CharPointer, U8, &key_mapper, "U", OS_Input_KeyU);
    HashmapAdd(CharPointer, U8, &key_mapper, "V", OS_Input_KeyV);
    HashmapAdd(CharPointer, U8, &key_mapper, "W", OS_Input_KeyW);
    HashmapAdd(CharPointer, U8, &key_mapper, "X", OS_Input_KeyX);
    HashmapAdd(CharPointer, U8, &key_mapper, "Y", OS_Input_KeyY);
    HashmapAdd(CharPointer, U8, &key_mapper, "Z", OS_Input_KeyZ);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad0", OS_Input_KeyNumpad0);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad1", OS_Input_KeyNumpad1);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad2", OS_Input_KeyNumpad2);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad3", OS_Input_KeyNumpad3);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad4", OS_Input_KeyNumpad4);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad5", OS_Input_KeyNumpad5);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad6", OS_Input_KeyNumpad6);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad7", OS_Input_KeyNumpad7);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad8", OS_Input_KeyNumpad8);
    HashmapAdd(CharPointer, U8, &key_mapper, "Numpad9", OS_Input_KeyNumpad9);
    HashmapAdd(
        CharPointer, U8, &key_mapper, "NumpadPlus", OS_Input_KeyNumpadPlus
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "NumpadMinus", OS_Input_KeyNumpadMinus
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "NumpadStar", OS_Input_KeyNumpadStar
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "NumpadSlash", OS_Input_KeyNumpadSlash
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "NumpadPeriod", OS_Input_KeyNumpadPeriod
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "LeftShift", OS_Input_KeyLeftShift
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "RightShift", OS_Input_KeyRightShift
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "LeftControl", OS_Input_KeyLeftControl
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "RightControl", OS_Input_KeyRightControl
    );
    HashmapAdd(CharPointer, U8, &key_mapper, "LeftAlt", OS_Input_KeyLeftAlt);
    HashmapAdd(CharPointer, U8, &key_mapper, "RightAlt", OS_Input_KeyRightAlt);
    HashmapAdd(CharPointer, U8, &key_mapper, "CapsLock", OS_Input_KeyCapsLock);
    HashmapAdd(
        CharPointer, U8, &key_mapper, "ScrollLock", OS_Input_KeyScrollLock
    );
    HashmapAdd(CharPointer, U8, &key_mapper, "NumLock", OS_Input_KeyNumLock);
    HashmapAdd(CharPointer, U8, &key_mapper, "Grave", OS_Input_KeyGrave);
    HashmapAdd(CharPointer, U8, &key_mapper, "Enter", OS_Input_KeyEnter);
    HashmapAdd(CharPointer, U8, &key_mapper, "Period", OS_Input_KeyPeriod);
    HashmapAdd(CharPointer, U8, &key_mapper, "Comma", OS_Input_KeyComma);
    HashmapAdd(
        CharPointer, U8, &key_mapper, "ForwardSlash", OS_Input_KeyForwardSlash
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "BackSlash", OS_Input_KeyBackSlash
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "Semicolon", OS_Input_KeySemicolon
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "Apostrophe", OS_Input_KeyApostrophe
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "OpenBracket", OS_Input_KeyOpenBracket
    );
    HashmapAdd(
        CharPointer, U8, &key_mapper, "CloseBracket", OS_Input_KeyCloseBracket
    );
    HashmapAdd(CharPointer, U8, &key_mapper, "Escape", OS_Input_KeyEscape);
    HashmapAdd(CharPointer, U8, &key_mapper, "Pause", OS_Input_KeyPause);
    HashmapAdd(CharPointer, U8, &key_mapper, "F1", OS_Input_KeyF1);
    HashmapAdd(CharPointer, U8, &key_mapper, "F2", OS_Input_KeyF2);
    HashmapAdd(CharPointer, U8, &key_mapper, "F3", OS_Input_KeyF3);
    HashmapAdd(CharPointer, U8, &key_mapper, "F4", OS_Input_KeyF4);
    HashmapAdd(CharPointer, U8, &key_mapper, "F5", OS_Input_KeyF5);
    HashmapAdd(CharPointer, U8, &key_mapper, "F6", OS_Input_KeyF6);
    HashmapAdd(CharPointer, U8, &key_mapper, "F7", OS_Input_KeyF7);
    HashmapAdd(CharPointer, U8, &key_mapper, "F8", OS_Input_KeyF8);
    HashmapAdd(CharPointer, U8, &key_mapper, "F9", OS_Input_KeyF9);
    HashmapAdd(CharPointer, U8, &key_mapper, "F10", OS_Input_KeyF10);
    HashmapAdd(CharPointer, U8, &key_mapper, "F11", OS_Input_KeyF11);
    HashmapAdd(CharPointer, U8, &key_mapper, "F12", OS_Input_KeyF12);
    HashmapAdd(CharPointer, U8, &key_mapper, "PageUp", OS_Input_KeyPageUp);
    HashmapAdd(CharPointer, U8, &key_mapper, "PageDown", OS_Input_KeyPageDown);
    HashmapAdd(CharPointer, U8, &key_mapper, "End", OS_Input_KeyEnd);
    HashmapAdd(CharPointer, U8, &key_mapper, "Home", OS_Input_KeyHome);
    HashmapAdd(CharPointer, U8, &key_mapper, "Insert", OS_Input_KeyInsert);
    HashmapAdd(CharPointer, U8, &key_mapper, "Delete", OS_Input_KeyDelete);
  }

  // CHECK FOR COLLISIONS
  {
    U8 v0 = HashmapGet(CharPointer, U8, &key_mapper, "MouseLeft");
    if (v0 != OS_Input_MouseButton_Left)
      Log("Collision on OS_Input_MouseButton_Left (old: %u, new: %u)",
          OS_Input_MouseButton_Left, v0);
    U8 v1 = HashmapGet(CharPointer, U8, &key_mapper, "MouseMiddle");
    if (v1 != OS_Input_MouseButton_Middle)
      Log("Collision on OS_Input_MouseButton_Middle (old: %u, new: %u)",
          OS_Input_MouseButton_Middle, v1);
    U8 v2 = HashmapGet(CharPointer, U8, &key_mapper, "MouseRight");
    if (v2 != OS_Input_MouseButton_Right)
      Log("Collision on OS_Input_MouseButton_Right (old: %u, new: %u)",
          OS_Input_MouseButton_Right, v2);
    U8 v3 = HashmapGet(CharPointer, U8, &key_mapper, "LeftArrow");
    if (v3 != OS_Input_KeyLeftArrow)
      Log("Collision on OS_Input_KeyLeftArrow (old: %u, new: %u)",
          OS_Input_KeyLeftArrow, v3);
    U8 v4 = HashmapGet(CharPointer, U8, &key_mapper, "UpArrow");
    if (v4 != OS_Input_KeyUpArrow)
      Log("Collision on OS_Input_KeyUpArrow (old: %u, new: %u)",
          OS_Input_KeyUpArrow, v4);
    U8 v5 = HashmapGet(CharPointer, U8, &key_mapper, "RightArrow");
    if (v5 != OS_Input_KeyRightArrow)
      Log("Collision on OS_Input_KeyRightArrow (old: %u, new: %u)",
          OS_Input_KeyRightArrow, v5);
    U8 v6 = HashmapGet(CharPointer, U8, &key_mapper, "DownArrow");
    if (v6 != OS_Input_KeyDownArrow)
      Log("Collision on OS_Input_KeyDownArrow (old: %u, new: %u)",
          OS_Input_KeyDownArrow, v6);
    U8 v7 = HashmapGet(CharPointer, U8, &key_mapper, "Minus");
    if (v7 != OS_Input_KeyMinus)
      Log("Collision on OS_Input_KeyMinus (old: %u, new: %u)",
          OS_Input_KeyMinus, v7);
    U8 v8 = HashmapGet(CharPointer, U8, &key_mapper, "Equals");
    if (v8 != OS_Input_KeyEquals)
      Log("Collision on OS_Input_KeyEquals (old: %u, new: %u)",
          OS_Input_KeyEquals, v8);
    U8 v9 = HashmapGet(CharPointer, U8, &key_mapper, "Backspace");
    if (v9 != OS_Input_KeyBackspace)
      Log("Collision on OS_Input_KeyBackspace (old: %u, new: %u)",
          OS_Input_KeyBackspace, v9);
    U8 v10 = HashmapGet(CharPointer, U8, &key_mapper, "0");
    if (v10 != OS_Input_Key0)
      Log("Collision on OS_Input_Key0 (old: %u, new: %u)", OS_Input_Key0, v10);
    U8 v11 = HashmapGet(CharPointer, U8, &key_mapper, "1");
    if (v11 != OS_Input_Key1)
      Log("Collision on OS_Input_Key1 (old: %u, new: %u)", OS_Input_Key1, v11);
    U8 v12 = HashmapGet(CharPointer, U8, &key_mapper, "2");
    if (v12 != OS_Input_Key2)
      Log("Collision on OS_Input_Key2 (old: %u, new: %u)", OS_Input_Key2, v12);
    U8 v13 = HashmapGet(CharPointer, U8, &key_mapper, "3");
    if (v13 != OS_Input_Key3)
      Log("Collision on OS_Input_Key3 (old: %u, new: %u)", OS_Input_Key3, v13);
    U8 v14 = HashmapGet(CharPointer, U8, &key_mapper, "4");
    if (v14 != OS_Input_Key4)
      Log("Collision on OS_Input_Key4 (old: %u, new: %u)", OS_Input_Key4, v14);
    U8 v15 = HashmapGet(CharPointer, U8, &key_mapper, "5");
    if (v15 != OS_Input_Key5)
      Log("Collision on OS_Input_Key5 (old: %u, new: %u)", OS_Input_Key5, v15);
    U8 v16 = HashmapGet(CharPointer, U8, &key_mapper, "6");
    if (v16 != OS_Input_Key6)
      Log("Collision on OS_Input_Key6 (old: %u, new: %u)", OS_Input_Key6, v16);
    U8 v17 = HashmapGet(CharPointer, U8, &key_mapper, "7");
    if (v17 != OS_Input_Key7)
      Log("Collision on OS_Input_Key7 (old: %u, new: %u)", OS_Input_Key7, v17);
    U8 v18 = HashmapGet(CharPointer, U8, &key_mapper, "8");
    if (v18 != OS_Input_Key8)
      Log("Collision on OS_Input_Key8 (old: %u, new: %u)", OS_Input_Key8, v18);
    U8 v19 = HashmapGet(CharPointer, U8, &key_mapper, "9");
    if (v19 != OS_Input_Key9)
      Log("Collision on OS_Input_Key9 (old: %u, new: %u)", OS_Input_Key9, v19);
    U8 v20 = HashmapGet(CharPointer, U8, &key_mapper, "A");
    if (v20 != OS_Input_KeyA)
      Log("Collision on OS_Input_KeyA (old: %u, new: %u)", OS_Input_KeyA, v20);
    U8 v21 = HashmapGet(CharPointer, U8, &key_mapper, "B");
    if (v21 != OS_Input_KeyB)
      Log("Collision on OS_Input_KeyB (old: %u, new: %u)", OS_Input_KeyB, v21);
    U8 v22 = HashmapGet(CharPointer, U8, &key_mapper, "C");
    if (v22 != OS_Input_KeyC)
      Log("Collision on OS_Input_KeyC (old: %u, new: %u)", OS_Input_KeyC, v22);
    U8 v23 = HashmapGet(CharPointer, U8, &key_mapper, "D");
    if (v23 != OS_Input_KeyD)
      Log("Collision on OS_Input_KeyD (old: %u, new: %u)", OS_Input_KeyD, v23);
    U8 v24 = HashmapGet(CharPointer, U8, &key_mapper, "E");
    if (v24 != OS_Input_KeyE)
      Log("Collision on OS_Input_KeyE (old: %u, new: %u)", OS_Input_KeyE, v24);
    U8 v25 = HashmapGet(CharPointer, U8, &key_mapper, "F");
    if (v25 != OS_Input_KeyF)
      Log("Collision on OS_Input_KeyF (old: %u, new: %u)", OS_Input_KeyF, v25);
    U8 v26 = HashmapGet(CharPointer, U8, &key_mapper, "G");
    if (v26 != OS_Input_KeyG)
      Log("Collision on OS_Input_KeyG (old: %u, new: %u)", OS_Input_KeyG, v26);
    U8 v27 = HashmapGet(CharPointer, U8, &key_mapper, "H");
    if (v27 != OS_Input_KeyH)
      Log("Collision on OS_Input_KeyH (old: %u, new: %u)", OS_Input_KeyH, v27);
    U8 v28 = HashmapGet(CharPointer, U8, &key_mapper, "I");
    if (v28 != OS_Input_KeyI)
      Log("Collision on OS_Input_KeyI (old: %u, new: %u)", OS_Input_KeyI, v28);
    U8 v29 = HashmapGet(CharPointer, U8, &key_mapper, "J");
    if (v29 != OS_Input_KeyJ)
      Log("Collision on OS_Input_KeyJ (old: %u, new: %u)", OS_Input_KeyJ, v29);
    U8 v30 = HashmapGet(CharPointer, U8, &key_mapper, "K");
    if (v30 != OS_Input_KeyK)
      Log("Collision on OS_Input_KeyK (old: %u, new: %u)", OS_Input_KeyK, v30);
    U8 v31 = HashmapGet(CharPointer, U8, &key_mapper, "L");
    if (v31 != OS_Input_KeyL)
      Log("Collision on OS_Input_KeyL (old: %u, new: %u)", OS_Input_KeyL, v31);
    U8 v32 = HashmapGet(CharPointer, U8, &key_mapper, "M");
    if (v32 != OS_Input_KeyM)
      Log("Collision on OS_Input_KeyM (old: %u, new: %u)", OS_Input_KeyM, v32);
    U8 v33 = HashmapGet(CharPointer, U8, &key_mapper, "N");
    if (v33 != OS_Input_KeyN)
      Log("Collision on OS_Input_KeyN (old: %u, new: %u)", OS_Input_KeyN, v33);
    U8 v34 = HashmapGet(CharPointer, U8, &key_mapper, "O");
    if (v34 != OS_Input_KeyO)
      Log("Collision on OS_Input_KeyO (old: %u, new: %u)", OS_Input_KeyO, v34);
    U8 v35 = HashmapGet(CharPointer, U8, &key_mapper, "P");
    if (v35 != OS_Input_KeyP)
      Log("Collision on OS_Input_KeyP (old: %u, new: %u)", OS_Input_KeyP, v35);
    U8 v36 = HashmapGet(CharPointer, U8, &key_mapper, "Q");
    if (v36 != OS_Input_KeyQ)
      Log("Collision on OS_Input_KeyQ (old: %u, new: %u)", OS_Input_KeyQ, v36);
    U8 v37 = HashmapGet(CharPointer, U8, &key_mapper, "R");
    if (v37 != OS_Input_KeyR)
      Log("Collision on OS_Input_KeyR (old: %u, new: %u)", OS_Input_KeyR, v37);
    U8 v38 = HashmapGet(CharPointer, U8, &key_mapper, "S");
    if (v38 != OS_Input_KeyS)
      Log("Collision on OS_Input_KeyS (old: %u, new: %u)", OS_Input_KeyS, v38);
    U8 v39 = HashmapGet(CharPointer, U8, &key_mapper, "T");
    if (v39 != OS_Input_KeyT)
      Log("Collision on OS_Input_KeyT (old: %u, new: %u)", OS_Input_KeyT, v39);
    U8 v40 = HashmapGet(CharPointer, U8, &key_mapper, "U");
    if (v40 != OS_Input_KeyU)
      Log("Collision on OS_Input_KeyU (old: %u, new: %u)", OS_Input_KeyU, v40);
    U8 v41 = HashmapGet(CharPointer, U8, &key_mapper, "V");
    if (v41 != OS_Input_KeyV)
      Log("Collision on OS_Input_KeyV (old: %u, new: %u)", OS_Input_KeyV, v41);
    U8 v42 = HashmapGet(CharPointer, U8, &key_mapper, "W");
    if (v42 != OS_Input_KeyW)
      Log("Collision on OS_Input_KeyW (old: %u, new: %u)", OS_Input_KeyW, v42);
    U8 v43 = HashmapGet(CharPointer, U8, &key_mapper, "X");
    if (v43 != OS_Input_KeyX)
      Log("Collision on OS_Input_KeyX (old: %u, new: %u)", OS_Input_KeyX, v43);
    U8 v44 = HashmapGet(CharPointer, U8, &key_mapper, "Y");
    if (v44 != OS_Input_KeyY)
      Log("Collision on OS_Input_KeyY (old: %u, new: %u)", OS_Input_KeyY, v44);
    U8 v45 = HashmapGet(CharPointer, U8, &key_mapper, "Z");
    if (v45 != OS_Input_KeyZ)
      Log("Collision on OS_Input_KeyZ (old: %u, new: %u)", OS_Input_KeyZ, v45);
    U8 v46 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad0");
    if (v46 != OS_Input_KeyNumpad0)
      Log("Collision on OS_Input_KeyNumpad0 (old: %u, new: %u)",
          OS_Input_KeyNumpad0, v46);
    U8 v47 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad1");
    if (v47 != OS_Input_KeyNumpad1)
      Log("Collision on OS_Input_KeyNumpad1 (old: %u, new: %u)",
          OS_Input_KeyNumpad1, v47);
    U8 v48 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad2");
    if (v48 != OS_Input_KeyNumpad2)
      Log("Collision on OS_Input_KeyNumpad2 (old: %u, new: %u)",
          OS_Input_KeyNumpad2, v48);
    U8 v49 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad3");
    if (v49 != OS_Input_KeyNumpad3)
      Log("Collision on OS_Input_KeyNumpad3 (old: %u, new: %u)",
          OS_Input_KeyNumpad3, v49);
    U8 v50 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad4");
    if (v50 != OS_Input_KeyNumpad4)
      Log("Collision on OS_Input_KeyNumpad4 (old: %u, new: %u)",
          OS_Input_KeyNumpad4, v50);
    U8 v51 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad5");
    if (v51 != OS_Input_KeyNumpad5)
      Log("Collision on OS_Input_KeyNumpad5 (old: %u, new: %u)",
          OS_Input_KeyNumpad5, v51);
    U8 v52 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad6");
    if (v52 != OS_Input_KeyNumpad6)
      Log("Collision on OS_Input_KeyNumpad6 (old: %u, new: %u)",
          OS_Input_KeyNumpad6, v52);
    U8 v53 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad7");
    if (v53 != OS_Input_KeyNumpad7)
      Log("Collision on OS_Input_KeyNumpad7 (old: %u, new: %u)",
          OS_Input_KeyNumpad7, v53);
    U8 v54 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad8");
    if (v54 != OS_Input_KeyNumpad8)
      Log("Collision on OS_Input_KeyNumpad8 (old: %u, new: %u)",
          OS_Input_KeyNumpad8, v54);
    U8 v55 = HashmapGet(CharPointer, U8, &key_mapper, "Numpad9");
    if (v55 != OS_Input_KeyNumpad9)
      Log("Collision on OS_Input_KeyNumpad9 (old: %u, new: %u)",
          OS_Input_KeyNumpad9, v55);
    U8 v56 = HashmapGet(CharPointer, U8, &key_mapper, "NumpadPlus");
    if (v56 != OS_Input_KeyNumpadPlus)
      Log("Collision on OS_Input_KeyNumpadPlus (old: %u, new: %u)",
          OS_Input_KeyNumpadPlus, v56);
    U8 v57 = HashmapGet(CharPointer, U8, &key_mapper, "NumpadMinus");
    if (v57 != OS_Input_KeyNumpadMinus)
      Log("Collision on OS_Input_KeyNumpadMinus (old: %u, new: %u)",
          OS_Input_KeyNumpadMinus, v57);
    U8 v58 = HashmapGet(CharPointer, U8, &key_mapper, "NumpadStar");
    if (v58 != OS_Input_KeyNumpadStar)
      Log("Collision on OS_Input_KeyNumpadStar (old: %u, new: %u)",
          OS_Input_KeyNumpadStar, v58);
    U8 v59 = HashmapGet(CharPointer, U8, &key_mapper, "NumpadSlash");
    if (v59 != OS_Input_KeyNumpadSlash)
      Log("Collision on OS_Input_KeyNumpadSlash (old: %u, new: %u)",
          OS_Input_KeyNumpadSlash, v59);
    U8 v60 = HashmapGet(CharPointer, U8, &key_mapper, "NumpadPeriod");
    if (v60 != OS_Input_KeyNumpadPeriod)
      Log("Collision on OS_Input_KeyNumpadPeriod (old: %u, new: %u)",
          OS_Input_KeyNumpadPeriod, v60);
    U8 v61 = HashmapGet(CharPointer, U8, &key_mapper, "LeftShift");
    if (v61 != OS_Input_KeyLeftShift)
      Log("Collision on OS_Input_KeyLeftShift (old: %u, new: %u)",
          OS_Input_KeyLeftShift, v61);
    U8 v62 = HashmapGet(CharPointer, U8, &key_mapper, "RightShift");
    if (v62 != OS_Input_KeyRightShift)
      Log("Collision on OS_Input_KeyRightShift (old: %u, new: %u)",
          OS_Input_KeyRightShift, v62);
    U8 v63 = HashmapGet(CharPointer, U8, &key_mapper, "LeftControl");
    if (v63 != OS_Input_KeyLeftControl)
      Log("Collision on OS_Input_KeyLeftControl (old: %u, new: %u)",
          OS_Input_KeyLeftControl, v63);
    U8 v64 = HashmapGet(CharPointer, U8, &key_mapper, "RightControl");
    if (v64 != OS_Input_KeyRightControl)
      Log("Collision on OS_Input_KeyRightControl (old: %u, new: %u)",
          OS_Input_KeyRightControl, v64);
    U8 v65 = HashmapGet(CharPointer, U8, &key_mapper, "LeftAlt");
    if (v65 != OS_Input_KeyLeftAlt)
      Log("Collision on OS_Input_KeyLeftAlt (old: %u, new: %u)",
          OS_Input_KeyLeftAlt, v65);
    U8 v66 = HashmapGet(CharPointer, U8, &key_mapper, "RightAlt");
    if (v66 != OS_Input_KeyRightAlt)
      Log("Collision on OS_Input_KeyRightAlt (old: %u, new: %u)",
          OS_Input_KeyRightAlt, v66);
    U8 v67 = HashmapGet(CharPointer, U8, &key_mapper, "CapsLock");
    if (v67 != OS_Input_KeyCapsLock)
      Log("Collision on OS_Input_KeyCapsLock (old: %u, new: %u)",
          OS_Input_KeyCapsLock, v67);
    U8 v68 = HashmapGet(CharPointer, U8, &key_mapper, "ScrollLock");
    if (v68 != OS_Input_KeyScrollLock)
      Log("Collision on OS_Input_KeyScrollLock (old: %u, new: %u)",
          OS_Input_KeyScrollLock, v68);
    U8 v69 = HashmapGet(CharPointer, U8, &key_mapper, "NumLock");
    if (v69 != OS_Input_KeyNumLock)
      Log("Collision on OS_Input_KeyNumLock (old: %u, new: %u)",
          OS_Input_KeyNumLock, v69);
    U8 v70 = HashmapGet(CharPointer, U8, &key_mapper, "Grave");
    if (v70 != OS_Input_KeyGrave)
      Log("Collision on OS_Input_KeyGrave (old: %u, new: %u)",
          OS_Input_KeyGrave, v70);
    U8 v71 = HashmapGet(CharPointer, U8, &key_mapper, "Enter");
    if (v71 != OS_Input_KeyEnter)
      Log("Collision on OS_Input_KeyEnter (old: %u, new: %u)",
          OS_Input_KeyEnter, v71);
    U8 v72 = HashmapGet(CharPointer, U8, &key_mapper, "Period");
    if (v72 != OS_Input_KeyPeriod)
      Log("Collision on OS_Input_KeyPeriod (old: %u, new: %u)",
          OS_Input_KeyPeriod, v72);
    U8 v73 = HashmapGet(CharPointer, U8, &key_mapper, "Comma");
    if (v73 != OS_Input_KeyComma)
      Log("Collision on OS_Input_KeyComma (old: %u, new: %u)",
          OS_Input_KeyComma, v73);
    U8 v74 = HashmapGet(CharPointer, U8, &key_mapper, "ForwardSlash");
    if (v74 != OS_Input_KeyForwardSlash)
      Log("Collision on OS_Input_KeyForwardSlash (old: %u, new: %u)",
          OS_Input_KeyForwardSlash, v74);
    U8 v75 = HashmapGet(CharPointer, U8, &key_mapper, "BackSlash");
    if (v75 != OS_Input_KeyBackSlash)
      Log("Collision on OS_Input_KeyBackSlash (old: %u, new: %u)",
          OS_Input_KeyBackSlash, v75);
    U8 v76 = HashmapGet(CharPointer, U8, &key_mapper, "Semicolon");
    if (v76 != OS_Input_KeySemicolon)
      Log("Collision on OS_Input_KeySemicolon (old: %u, new: %u)",
          OS_Input_KeySemicolon, v76);
    U8 v77 = HashmapGet(CharPointer, U8, &key_mapper, "Apostrophe");
    if (v77 != OS_Input_KeyApostrophe)
      Log("Collision on OS_Input_KeyApostrophe (old: %u, new: %u)",
          OS_Input_KeyApostrophe, v77);
    U8 v78 = HashmapGet(CharPointer, U8, &key_mapper, "OpenBracket");
    if (v78 != OS_Input_KeyOpenBracket)
      Log("Collision on OS_Input_KeyOpenBracket (old: %u, new: %u)",
          OS_Input_KeyOpenBracket, v78);
    U8 v79 = HashmapGet(CharPointer, U8, &key_mapper, "CloseBracket");
    if (v79 != OS_Input_KeyCloseBracket)
      Log("Collision on OS_Input_KeyCloseBracket (old: %u, new: %u)",
          OS_Input_KeyCloseBracket, v79);
    U8 v80 = HashmapGet(CharPointer, U8, &key_mapper, "Escape");
    if (v80 != OS_Input_KeyEscape)
      Log("Collision on OS_Input_KeyEscape (old: %u, new: %u)",
          OS_Input_KeyEscape, v80);
    U8 v81 = HashmapGet(CharPointer, U8, &key_mapper, "Pause");
    if (v81 != OS_Input_KeyPause)
      Log("Collision on OS_Input_KeyPause (old: %u, new: %u)",
          OS_Input_KeyPause, v81);
    U8 v82 = HashmapGet(CharPointer, U8, &key_mapper, "F1");
    if (v82 != OS_Input_KeyF1)
      Log("Collision on OS_Input_KeyF1 (old: %u, new: %u)", OS_Input_KeyF1,
          v82);
    U8 v83 = HashmapGet(CharPointer, U8, &key_mapper, "F2");
    if (v83 != OS_Input_KeyF2)
      Log("Collision on OS_Input_KeyF2 (old: %u, new: %u)", OS_Input_KeyF2,
          v83);
    U8 v84 = HashmapGet(CharPointer, U8, &key_mapper, "F3");
    if (v84 != OS_Input_KeyF3)
      Log("Collision on OS_Input_KeyF3 (old: %u, new: %u)", OS_Input_KeyF3,
          v84);
    U8 v85 = HashmapGet(CharPointer, U8, &key_mapper, "F4");
    if (v85 != OS_Input_KeyF4)
      Log("Collision on OS_Input_KeyF4 (old: %u, new: %u)", OS_Input_KeyF4,
          v85);
    U8 v86 = HashmapGet(CharPointer, U8, &key_mapper, "F5");
    if (v86 != OS_Input_KeyF5)
      Log("Collision on OS_Input_KeyF5 (old: %u, new: %u)", OS_Input_KeyF5,
          v86);
    U8 v87 = HashmapGet(CharPointer, U8, &key_mapper, "F6");
    if (v87 != OS_Input_KeyF6)
      Log("Collision on OS_Input_KeyF6 (old: %u, new: %u)", OS_Input_KeyF6,
          v87);
    U8 v88 = HashmapGet(CharPointer, U8, &key_mapper, "F7");
    if (v88 != OS_Input_KeyF7)
      Log("Collision on OS_Input_KeyF7 (old: %u, new: %u)", OS_Input_KeyF7,
          v88);
    U8 v89 = HashmapGet(CharPointer, U8, &key_mapper, "F8");
    if (v89 != OS_Input_KeyF8)
      Log("Collision on OS_Input_KeyF8 (old: %u, new: %u)", OS_Input_KeyF8,
          v89);
    U8 v90 = HashmapGet(CharPointer, U8, &key_mapper, "F9");
    if (v90 != OS_Input_KeyF9)
      Log("Collision on OS_Input_KeyF9 (old: %u, new: %u)", OS_Input_KeyF9,
          v90);
    U8 v91 = HashmapGet(CharPointer, U8, &key_mapper, "F10");
    if (v91 != OS_Input_KeyF10)
      Log("Collision on OS_Input_KeyF10 (old: %u, new: %u)", OS_Input_KeyF10,
          v91);
    U8 v92 = HashmapGet(CharPointer, U8, &key_mapper, "F11");
    if (v92 != OS_Input_KeyF11)
      Log("Collision on OS_Input_KeyF11 (old: %u, new: %u)", OS_Input_KeyF11,
          v92);
    U8 v93 = HashmapGet(CharPointer, U8, &key_mapper, "F12");
    if (v93 != OS_Input_KeyF12)
      Log("Collision on OS_Input_KeyF12 (old: %u, new: %u)", OS_Input_KeyF12,
          v93);
    U8 v94 = HashmapGet(CharPointer, U8, &key_mapper, "PageUp");
    if (v94 != OS_Input_KeyPageUp)
      Log("Collision on OS_Input_KeyPageUp (old: %u, new: %u)",
          OS_Input_KeyPageUp, v94);
    U8 v95 = HashmapGet(CharPointer, U8, &key_mapper, "PageDown");
    if (v95 != OS_Input_KeyPageDown)
      Log("Collision on OS_Input_KeyPageDown (old: %u, new: %u)",
          OS_Input_KeyPageDown, v95);
    U8 v96 = HashmapGet(CharPointer, U8, &key_mapper, "End");
    if (v96 != OS_Input_KeyEnd)
      Log("Collision on OS_Input_KeyEnd (old: %u, new: %u)", OS_Input_KeyEnd,
          v96);
    U8 v97 = HashmapGet(CharPointer, U8, &key_mapper, "Home");
    if (v97 != OS_Input_KeyHome)
      Log("Collision on OS_Input_KeyHome (old: %u, new: %u)", OS_Input_KeyHome,
          v97);
    U8 v98 = HashmapGet(CharPointer, U8, &key_mapper, "Insert");
    if (v98 != OS_Input_KeyInsert)
      Log("Collision on OS_Input_KeyInsert (old: %u, new: %u)",
          OS_Input_KeyInsert, v98);
    U8 v99 = HashmapGet(CharPointer, U8, &key_mapper, "Delete");
    if (v99 != OS_Input_KeyDelete)
      Log("Collision on OS_Input_KeyDelete (old: %u, new: %u)",
          OS_Input_KeyDelete, v99);
  }

  ArenaRelease(&arena);
  return 0;
}

static F32 MoveSp      = 0.25f;
static F32 Sensitivity = 0.15f;
static F32 Yaw         = -90.f;
static F32 Pitch       = 0.f;

static Vec2F32 MousePos = {0};
static F32 _lastX       = 0.f;
static F32 _lastY       = 0.f;

static Vec3F32 Input = {0};

void ProcessWindowInput(OS_Window* window, U32 key, OS_WindowKeyAction action)
{
  if (key == GLFW_KEY_ESCAPE && action == WindowKeyAction_Down)
    OS_WindowSetOpen(window, 0);
}

void CursorPositionCallback(OS_Window* window, F32 x, F32 y)
{
  F32 xoff = (x - _lastX) * Sensitivity;
  F32 yoff = (_lastY - y) * Sensitivity;

  _lastX = x;
  _lastY = y;

  Yaw += xoff;
  Pitch += yoff;

  if (Pitch > 89.0f)
    Pitch = 89.0f;
  if (Pitch < -89.0f)
    Pitch = -89.0f;
}

void ScrollCallback(OS_Window* window, F32 x, F32 y)
{
  Log("Scrolled: (%.2f, %.2f)", x, y);
}

int __main()
{
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Gigabytes(1));

  OS_Init();
  OS_Window window = {0};
  OS_WindowInit(&window, 1280, 720, Str8Lit("OS Window"));

  OS_WindowRegisterKeyCallback(&window, ProcessWindowInput);
  OS_WindowRegisterMousePositionCallback(&window, CursorPositionCallback);
  OS_WindowRegisterScrollCallback(&window, ScrollCallback);
  OS_WindowSetMouseVisibility(&window, WindowMouseVisibility_Disabled);

  String8 path = OS_PathRelative(
      &arena, OS_PathExecutableDir(&arena), Str8Lit("./assets/data/input.toml")
  );

  I_InputMap input_map = {0};
  I_InputMapInit(&input_map, &arena, path);
  if (!I_InputMapSchemeSetActive(&input_map, "mouse_keyboard"))
    Log("Failed setting active input scheme!", "");
  if (!I_InputMapContextActivate(&input_map, "ingame"))
    Log("Failed setting active input context!", "");

  R_RenderInit(&window);

  R_Camera camera = R_CameraMakePerspective(
      Vec3F32_MultScalar(Vec3F32_Forward, -10.f), Vec3F32_Forward, Vec3F32_Up,
      90.f, (F32)window.width / (F32)window.height, 0.1f, 100.f
  );
  //   R_Camera camera = R_CameraMakeOrthographic(
  //       Vec3F32_MultScalar(Vec3F32_Forward, -10.f), Vec3F32_Forward,
  //       Vec3F32_Up, 10.f, (F32)window.width / (F32)window.height, 0.1f, 100.f
  //   );

  R_Framebuffer framebuffer = R_FramebufferMake(
      320, 180, TextureWrap_ClampToEdge, TextureFilter_Nearest,
      TextureFormat_RGB, 1
  );

  // Data
  F32 vertices[] = {
      -1.0f, -1.0f, -1.0f, // 0
      1.0f,  0.0f,  0.0f,  // Red
      1.0f,  -1.0f, -1.0f, // 1
      0.0f,  1.0f,  0.0f,  // Green
      1.0f,  1.0f,  -1.0f, // 2
      0.0f,  0.0f,  1.0f,  // Blue
      -1.0f, 1.0f,  -1.0f, // 3
      1.0f,  1.0f,  0.0f,  // Yellow
      -1.0f, -1.0f, 1.0f,  // 4
      1.0f,  0.0f,  1.0f,  // Magenta
      1.0f,  -1.0f, 1.0f,  // 5
      0.0f,  1.0f,  1.0f,  // Cyan
      1.0f,  1.0f,  1.0f,  // 6
      1.0f,  1.0f,  1.0f,  // White
      -1.0f, 1.0f,  1.0f,  // 7
      0.0f,  0.0f,  0.0f   // Black
  };
  U32 indices[] = {
      0, 1, 2, 2, 3, 0, // Front
      4, 5, 6, 6, 7, 4, // Back
      1, 5, 6, 6, 2, 1, // Right
      0, 4, 7, 7, 3, 0, // Left
      3, 2, 6, 6, 7, 3, // Top
      0, 1, 5, 5, 4, 0  // Bottom
  };

  // Create a vertex buffer
  R_Buffer vertex_buffer = {0};
  R_BufferInit(&vertex_buffer, BufferFlag_Type_Vertex);
  R_BufferData(&vertex_buffer, vertices, sizeof(vertices));

  // Create an index buffer
  R_Buffer index_buffer = {0};
  R_BufferInit(&index_buffer, BufferFlag_Type_Index);
  R_BufferData(&index_buffer, indices, sizeof(indices));

  // Do some shaders real quick.
  String8 exe_path = OS_PathExecutableDir(&arena);

  String8 vs_path = OS_PathRelative(
      &arena, exe_path, Str8Lit("./assets/shaders/default_vert.vs")
  );
  R_Shader vs = R_ShaderMake(&arena, vs_path, ShaderType_Vertex);

  String8 fs_path = OS_PathRelative(
      &arena, exe_path, Str8Lit("./assets/shaders/default_frag.fs")
  );
  R_Shader fs = R_ShaderMake(&arena, fs_path, ShaderType_Fragment);

  R_Shader* shaders[2] = {&vs, &fs};
  R_ShaderPack program;
  R_ShaderPackInit(&program, shaders, 2, &arena, 7);

  // Create the actual rendering pipeline.
  R_Attribute vertex_attribs[2];
  vertex_attribs[0].name = Str8Lit("Position");
  vertex_attribs[0].type = AttributeType_F3;
  vertex_attribs[1].name = Str8Lit("Colour");
  vertex_attribs[1].type = AttributeType_F3;

  R_Pipeline pipeline;
  R_PipelineInit(&pipeline, &program, vertex_attribs, 2);
  R_PipelineAddBuffer(&pipeline, &vertex_buffer);
  R_PipelineAddBuffer(&pipeline, &index_buffer);

  // Some texture action lol
  String8 texture_path =
      OS_PathRelative(&arena, exe_path, Str8Lit("./assets/sprites/player.jpg"));

  S32 x, y, channels;
  stbi_set_flip_vertically_on_load(1);
  char* data = stbi_load((const char*)texture_path.data, &x, &y, &channels, 0);

  R_Texture texture;
  R_TextureInit(
      &texture, x, y, TextureWrap_ClampToEdge, TextureWrap_ClampToEdge,
      TextureFilter_Nearest, TextureFilter_Nearest, TextureFormat_RGB, NULL
  );

  R_TextureData(&texture, (void*)data);

  stbi_image_free(data);

  PrecisionTime elapsed_time      = 0;
  PrecisionTime prev_loop_time    = 0;
  PrecisionTime current_loop_time = 0;
  PrecisionTime delta_time        = 0;

  // Model Matrix (local to world)
  Mat4x4F32 model_matrix = Mat4x4_MakeValue(0.f);

  Vec3F32 translate = Vec3F32_Make(0.f, 0.f, 0.f);
  Vec3F32 scale     = Vec3F32_Make(1.f, 1.f, 1.f);
  Mat4x4F32 rotation =
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(0.f, 0.f, 0.f));

  Vec3F32 cube_positions[] = {
      Vec3F32_Make(0.f, 0.f, 0.f),
      Vec3F32_Make(0.f, 20.f, 15.f),
      Vec3F32_Make(32.f, -27.f, 0.f),
      Vec3F32_Make(-36.f, 0.f, -29.f),
  };

  Mat4x4F32 cube_rotations[] = {
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(0.f, 0.f, 0.f)),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(12.f, 106.f, 259.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(172.f, 206.f, 82.f)
      ),
      QuatF32_Mat4x4FromQuatF32(QuatF32_MakeFromEulerAngles(84.f, 29.f, 169.f)),
  };

  Vec3F32 cube_scales[] = {
      Vec3F32_Make(1.f, 1.f, 1.f),
      Vec3F32_Make(0.5f, 1.7f, 5.2f),
      Vec3F32_Make(2.5f, 8.f, 0.2f),
      Vec3F32_Make(1.f, 1.f, 1.f),
  };

  Log("Starting game loop.", "");
  while (OS_WindowIsOpen(&window))
  {
    current_loop_time = OS_TimeMicroseconds();
    delta_time        = current_loop_time - prev_loop_time;
    elapsed_time      = elapsed_time + delta_time;

    // 60 FPS, both render and update
    if (delta_time > 16000)
    {
      OS_WindowPollEvents();
      I_InputMapUpdate(&input_map);

      // I_InputMapContextAction* fire_action;
      // if (I_InputMapActionTryGet(&input_map, "ingame", "fire", &fire_action))
      // {
      //   if (fire_action->value.button.value)
      //     Log("Fire!", "");
      // }

      I_InputMapContextAction* m;
      if (I_InputMapActionTryGet(&input_map, "ingame", "move_horizontal", &m))
      {
        Log("Horizontal Value: %f", m->value.range_1d.value);
      }

      Input.x = OS_InputKey('D') - OS_InputKey('A');
      Input.y = OS_InputKey(' ') - OS_InputKey(OS_Input_KeyLeftShift);
      Input.z = OS_InputKey('W') - OS_InputKey('S');
      Input   = Vec3F32_Normalize(Input);

      Vec3F32 x_axis = Vec3F32_MultScalar(
          Vec3F32_Cross(camera.forward, camera.up), Input.x * MoveSp
      );
      Vec3F32 y_axis   = Vec3F32_MultScalar(camera.up, Input.y * MoveSp);
      Vec3F32 z_axis   = Vec3F32_MultScalar(camera.forward, Input.z * MoveSp);
      Vec3F32 movement = Vec3F32_Add(Vec3F32_Add(x_axis, y_axis), z_axis);
      camera.position  = Vec3F32_Add(camera.position, movement);

      Vec3F32 direction;
      direction.x = F32_Cos(F32_DegToRad(Yaw)) * F32_Cos(F32_DegToRad(Pitch));
      direction.y = F32_Sin(F32_DegToRad(Pitch));
      direction.z = F32_Sin(F32_DegToRad(Yaw)) * F32_Cos(F32_DegToRad(Pitch));
      camera.forward = Vec3F32_Normalize(direction);

      R_CameraUpdateMatrices(&camera);

      // Render
      R_FramebufferBind(&framebuffer);
      R_FramebufferSetViewport(&framebuffer);
      glEnable(GL_DEPTH_TEST);

      glDepthMask(GL_TRUE);
      R_ClearDepthBuffer();
      R_ClearColourBuffer(0.2f, 0.1f, 0.3f);

      // R_TextureBind(&texture, 0);
      R_PipelineBind(&pipeline);

      // TODO(calco): Have this in a draw class.
      // For now manually sending camera data to shaders.
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("view"), camera.view_matrix.elements[0]
      );
      R_ShaderPackUploadMat4(
          pipeline.shader_pack, Str8Lit("projection"),
          camera.projection_matrix.elements[0]
      );

      for (U64 i = 0; i < 1; ++i)
      {
        // Model Matrix
        model_matrix = Mat4x4_Mult(
            Mat4x4_MakeTranslate(Vec3F32_Add(translate, cube_positions[i])),
            Mat4x4_Mult(
                Mat4x4_Mult(rotation, cube_rotations[i]),
                Mat4x4_MakeScale(Vec3F32_Add(scale, cube_scales[i]))
            )
        );

        R_ShaderPackUploadMat4(
            pipeline.shader_pack, Str8Lit("model"), model_matrix.elements[0]
        );

        glDrawElements(
            GL_TRIANGLES, sizeof(indices) / sizeof(U32), GL_UNSIGNED_INT,
            (void*)0
        );
      }

      R_FramebufferBlitToScreenBuffer(&framebuffer, &window);

      R_RenderSwapchain(&window);
      prev_loop_time = current_loop_time;
    }
  }

  // Clean up after OpenGL
  R_BufferFreeGPU(&vertex_buffer);
  R_BufferFreeGPU(&index_buffer);

  R_ShaderFreeGPU(&vs);
  R_ShaderFreeGPU(&fs);
  R_ShaderPackFreeGPU(&program);

  R_PipelineFreeGPU(&pipeline);

  R_FramebufferFreeGPU(&framebuffer);

  OS_WindowFree(&window);

  ArenaRelease(&arena);
  return 0;
}