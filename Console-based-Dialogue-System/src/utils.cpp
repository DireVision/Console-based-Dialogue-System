#include "utils.h"

bool g_running = true;

void Exit()
{
  g_running = false;
}

void PressAnyKeyToContinue()
{
  std::cout << "\n\n Press any key to continue...\n";
  _getch();
}

int SelectDialogueOption(int max)
{
  std::cout << "\n\n Pick a dialogue option...\n";
  int option = 0;

  // check if getch is a number
  if (_getch() >= 48 && _getch() <= 57)
  {
    option = _getch() - 48;
  }
  else
  {
    throw Exception_Input_NaN(" Error: Input is not a number.\n");
  }

  // check if the number is within the range
  if (option < 1 || option > max)
  {
    throw Exception_Input_OutOfRange(" Error: [ " + std::to_string(option) + " ] is not a valid dialogue option.\n");
  }

  return option;
}

void ClearScreen()
{
  system("cls");
}