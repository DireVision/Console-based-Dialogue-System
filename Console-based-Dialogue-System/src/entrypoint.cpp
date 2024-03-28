#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <windows.h>

#include <thread>

#include "frame_rate_controller.h"
#include "state_manager.h"
#include "menu_state.h"
#include "file_manager.h"
#include "dlg_parser.h"

using namespace Engine;

int main()
{
#ifdef _DEBUG
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  // initialize COM library
  CoInitialize(nullptr);

  // set the initial state
  StateManager::SetState(std::make_shared<MenuState>());

  // main loop
  while (g_running)
  {
    FrameRateController::StartFrame();

    StateManager::Update(FrameRateController::GetFrameTime());

    // force quit
    if (_kbhit())
    {
      char key = _getch();
      if (key == 'q') Exit();
    }

    FrameRateController::EndFrame();
  }

  StateManager::Exit();
  
  // uninitialize COM library
  CoUninitialize();
  return 0;
}