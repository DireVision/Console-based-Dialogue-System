#include "utils.h"

#include "file.h"
using namespace Engine;

namespace Prompt
{

  void PressStartToPlay();
  void PressAnyKeyToContinue();
  void PickADialogueOption();
  void PickAMenuOption();

}

namespace Screen
{

  int Title();
  int MainMenu();
  int DisplayDlgFiles(std::vector<File> files);

}
