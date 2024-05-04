#include "DisplayManager.h"

void DisplayManager::PrintDialogue(std::pair<std::string, std::string> const& speaker_dialogue_pair)
{
  std::cout << menu << "\n\n";

  if (!speaker_dialogue_pair.first.empty())
  {
    std::cout << "    " << std::string(6 + speaker_dialogue_pair.first.length(), '-') << '\n' <<
      "    " << "|  " << speaker_dialogue_pair.first << "  |\n" << 
      "    " << std::string(6 + speaker_dialogue_pair.first.length(), '-') << '\n';
  }
  std::cout << "\n " << speaker_dialogue_pair.second; // With the extra one space to make the dialogue look nicer.
}

void DisplayManager::PrintToScreen(const std::string& content)
{
  std::cout << menu << "\n\n";

  std::cout << content;
}

void DisplayManager::PrintWithoutMenu(const std::string& content)
{
  std::cout << content;
}