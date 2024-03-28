#pragma once

#include <chrono>

namespace Engine
{

  class FrameRateController
  {
  public:
    static void StartFrame();
    static void EndFrame();

    static void SetTargetFrameRate(int target_frame_rate = 60);

    static int GetTargetFrameRate();
    static int GetFrameRate();
    static float GetFrameTime();

  private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> m_last_frame_time;
    static int m_target_frame_rate;
    static float m_frame_time;
  };

}
