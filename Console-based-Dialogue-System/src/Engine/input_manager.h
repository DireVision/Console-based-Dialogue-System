#pragma once

#include <conio.h>
#include <iostream>
#include <windows.h>

#include "keys.h"

namespace Engine
{

  class InputManager
  {
    static bool keys[256];
    static bool keys_prev[256];
    static bool keys_pressed[256];
    static bool keys_released[256];

    static void PollKeys()
    {
      for (int i = 0; i < 256; i++)
      {
        keys_prev[i] = keys[i];
        keys[i] = GetAsyncKeyState(i) & 0x8000;
        keys_pressed[i] = !keys_prev[i] && keys[i];
        keys_released[i] = keys_prev[i] && !keys[i];
      }
    }
  };

}
