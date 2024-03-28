#include "frame_rate_controller.h"

#include <thread>

namespace Engine
{

  // static member initialization
  std::chrono::time_point<std::chrono::high_resolution_clock> FrameRateController::m_last_frame_time = std::chrono::high_resolution_clock::now();
  int FrameRateController::m_target_frame_rate = 60;
  float FrameRateController::m_frame_time = 0.0f;

  void FrameRateController::StartFrame()
  {
    m_last_frame_time = std::chrono::high_resolution_clock::now();
  }

  void FrameRateController::EndFrame()
  {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto frame_duration = std::chrono::duration<float, std::chrono::seconds::period>(current_time - m_last_frame_time);
    m_frame_time = frame_duration.count();
    //auto target_frame_duration = std::chrono::duration<float, std::chrono::seconds::period>(1.0f / m_target_frame_rate);
    //if (frame_duration < target_frame_duration)
    //{
    //  std::chrono::duration<float, std::chrono::seconds::period> sleep_time = target_frame_duration - frame_duration;
    //  std::this_thread::sleep_for(sleep_time);
    //}
  }

  void FrameRateController::SetTargetFrameRate(int target_frame_rate)
  {
    m_target_frame_rate = target_frame_rate;
  }

  int FrameRateController::GetTargetFrameRate()
  {
    return m_target_frame_rate;
  }

  int FrameRateController::GetFrameRate()
  {
    return static_cast<int>(1.0f / m_frame_time);
  }

  float FrameRateController::GetFrameTime()
  {
    return m_frame_time;
  }

}