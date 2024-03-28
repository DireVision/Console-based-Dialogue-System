#include "menu_state.h"

#include <conio.h>
#include <iostream>

void MenuState::OnEnter()
{
  std::cout << "MenuState::OnEnter()" << std::endl;
}

void MenuState::OnExit()
{
  std::cout << "MenuState::OnExit()" << std::endl;
}

void MenuState::Update(float dt)
{
  if (_kbhit()) {
    char ch = _getch();
    if (ch >= 0 && ch <= 224)
    {
      std::cout << ch;
    }
  }
}

void MenuState::Draw(float dt)
{
}
