#pragma once

#include "state.h"

class MenuState : public IState
{
public:
  void OnEnter() override;
  void Update(float dt) override;
  void Draw(float dt) override;
  void OnExit() override;
};
