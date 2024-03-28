#pragma once

class IState
{
public:
  virtual void OnEnter() = 0;
  virtual void Update(float dt) = 0;
  virtual void Draw(float dt) = 0;
  virtual void OnExit() = 0;
};
