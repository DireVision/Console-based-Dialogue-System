#include "renderer.h"

#include "frame_rate_controller.h"

#include <thread>

namespace Engine
{

  void Renderer::RenderThread()
  {
    float accumulated_time = 0.0f;

    while (g_running)
    {
      // draw at the target frame rate
      accumulated_time += FrameRateController::GetFrameTime();
      if (accumulated_time <= 1.f / FrameRateController::GetTargetFrameRate()) return;

      // draw frame
      accumulated_time -= 1.f / FrameRateController::GetTargetFrameRate();
      auto data = CreateNewFrame();
      Draw(data);
      Flush();
    }
  }

}