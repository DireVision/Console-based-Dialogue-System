#include "state_manager.h"

#include "frame_rate_controller.h"

namespace Engine
{

  // static member initialization
  std::shared_ptr<IState> StateManager::m_state_current = nullptr;

  void StateManager::SetState(std::shared_ptr<IState> state)
  {
    // no state
    if (!state) return;

    // same state
    if (state == m_state_current) return;

    // set the next state
    Exit();
    m_state_current = state;
    m_state_current->OnEnter();
  }

  void StateManager::Update(float dt)
  {
    // no state
    if (!m_state_current) return;

    m_state_current->Update(dt);

    // only draw at the correct fps
    FrameRateController::GetFrameRate

    m_state_current->Draw(dt);
  }

  void StateManager::Restart()
  {
    // no state
    if (!m_state_current) return;

    m_state_current->OnExit();
    m_state_current->OnEnter();
  }

  void StateManager::Exit()
  {
    if (m_state_current) m_state_current->OnExit();
    m_state_current = nullptr;
  }

}
