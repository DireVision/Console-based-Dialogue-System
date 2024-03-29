#include "display.h"

namespace Prompt
{

  void PressStartToPlay()
  {
    std::cout << "\n Press any key to start...\n";
  }

  void PressAnyKeyToContinue()
  {
    std::cout << "\n Press any key to continue...\n";
  }

  void PickADialogueOption()
  {
    std::cout << "\n Pick a dialogue option...\n";
  }

  void PickAMenuOption()
  {
    std::cout << "\n Pick a menu option...\n";
  }

}

namespace Screen
{

  int Title()
  {
    std::cout
      << "\n"
      << " ||=============================================||\n"
      << " ||        Console-based Dialogue System        ||\n"
      << " ||            ~ Made by Wen Loong ~            ||\n"
      << " ||                                             ||\n"
      << " ||            Press [0] at any time            ||\n"
      << " ||              to quit the game!              ||\n"
      << " ||=============================================||\n"
      << "\n"
    ;
    if (player_name.length() > 0)
    {
      std::cout << " >>> Logged in as: " << player_name << "! <<<\n\n";
    }
    return 0;
  }

  int MainMenu()
  {
    // menu options
    std::cout
      << " [1] Pick a dialogue from the assets folder\n"
      << " [2] Load dialogue from file\n"
      << " [3] Quit\n"
    ;
    return 3;
  }

  int DisplayDlgFiles(std::vector<File> files)
  {
    // display dialogue files
    for (int i = 0; i < files.size(); i++)
    {
      std::cout << " [" << i + 1 << "] " << files[i];
    }
    std::cout << "\n";
    return static_cast<int>(files.size());
  }

}
