#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "base/base_include.h"
#include "os/os.h"

LRESULT
MainWindowProc(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam)
{
  LRESULT result = 0;

  switch (message)
  {
    case WM_SIZE:
    {
      printf("App got resized.\n");
    }
    break;
    case WM_DESTROY:
    {
      printf("App got destroyed.\n");
    }
    break;
    case WM_CLOSE:
    {
      printf("App got closed.\n");
    }
    break;
    case WM_ACTIVATEAPP:
    {
      printf("App got activated.\n");
    }
    break;
    default:
    {
      // Call windows default to handle what we don't want custom behaviour for
      result = DefWindowProcA(window_handle, message, wparam, lparam);
    }
    break;
  }

  return result;
}

int main()
{
  M_BaseMemory memory = OS_BaseMemory();
  Arena arena;
  ArenaInit(&arena, &memory, Megabytes(1));

  // Set up window_class using Windows lmao
  HANDLE instance_handle = GetModuleHandleA(0);
  WNDCLASS window_class = {0};
  window_class.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
  window_class.lpfnWndProc = MainWindowProc;
  window_class.hInstance = instance_handle;
  window_class.hIcon = NULL;
  window_class.lpszClassName = "CalcoWindowClass";

  if (RegisterClassA(&window_class))
  {
    HWND window_handle = CreateWindowExA(
        NULL,                             //
        window_class.lpszClassName,       //
        "Hello Windows",                  //
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, //
        CW_USEDEFAULT, CW_USEDEFAULT,     //
        CW_USEDEFAULT, CW_USEDEFAULT,     //
        NULL,                             //
        NULL,                             //
        instance_handle,                  //
        NULL                              //
    );

    if (window_handle != NULL)
    {
      MSG message = {0};

      while (1)
      {
        BOOL msg_result = GetMessageA(&message, NULL, NULL, NULL);
        if (msg_result <= 0)
        {
          break;
        }

        TranslateMessage(&message);
        DispatchMessageA(&message);
      }
    }
    else
    {
      printf("Error creating the window.\n");
    }
  }
  else
  {
    printf("Error registering window class.\n");
  }

  ArenaRelease(&arena);
  return 0;
}