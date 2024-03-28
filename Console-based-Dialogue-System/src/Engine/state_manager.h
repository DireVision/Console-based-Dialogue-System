#pragma once

#include "state.h"
#include <memory>

namespace Engine
{

  class StateManager
  {
    static std::shared_ptr<IState> m_state_current;

  public:
    static void SetState(std::shared_ptr<IState> state);
    static void Restart();
    static void Update(float dt);
    static void Exit();
  };

}
