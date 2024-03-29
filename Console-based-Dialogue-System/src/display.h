#include "utils.h"

#include "file.h"

namespace Prompt
{

  void PressStartToPlay()
  {
    std::cout << " Press any key to start...\n";
  }

  void PressAnyKeyToContinue()
  {
    std::cout << " Press any key to continue...\n";
  }

  void PickADialogueOption()
  {
    std::cout << " Pick a dialogue option...\n";
  }

  void PickAMenuOption()
  {
    std::cout << " Pick a menu option...\n";
  }

}

namespace Screen
{

  int Title()
  {
    std::cout
      << "\n"
      << " ||===============================||\n"
      << " || Console-based Dialogue System ||\n"
      << " ||       Made by Wen Loong       ||\n"
      << " ||                               ||\n"
      << " ||    Press [ 0 ] at any time    ||\n"
      << " ||       to quit the game!       ||\n"
      << " ||===============================||\n"
      << "\n"
    ;
    return 0;
  }

  int MainMenu()
  {
    // menu options
    std::cout
      << " 1. Pick a dialogue from the assets folder\n"
      << " 2. Load dialogue from file\n"
      << " 3. Exit\n"
    ;
    return 3;
  }

  int DisplayDlgFiles(std::vector<Engine::File> files)
  {
    // display dialogue files
    int i = 1;
    for (const auto& file : files)
    {
      std::cout << i << ". " << file;
      i++;
    }
    return i;
  }

}
