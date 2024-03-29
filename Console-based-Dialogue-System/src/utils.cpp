#include "utils.h"

bool WaitForInput()
{
  return _getch() == 48;
}

int SelectOption(int max)
{
  int option = 0;

  char ch = _getch();

  // check if getch is 0
  if (ch == 48)
  {
    return 0;
  }
  // check if getch is a number
  else if (ch >= 49 && ch <= 57)
  {
    option = ch - 48;
  }
  else
  {
    throw Exception_Input_NaN(" Error: Input is not a number.\n");
  }

  // check if the number is within the range
  if (option < 1 || option > max)
  {
    throw Exception_Input_OutOfRange(" Error: [ " + std::to_string(option) + " ] is not a valid option.\n");
  }

  return option;
}

void ClearScreen()
{
  system("cls");
}