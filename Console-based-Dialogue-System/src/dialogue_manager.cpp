#include "dialogue_manager.h"

Document DialogueManager::current_dialogue;
std::vector<File> DialogueManager::dialogue_files;

std::vector<File>& DialogueManager::FilterDialogueFiles(const std::vector<File>& files)
{
  dialogue_files.clear();
  for (const auto& file : files)
  {
    if (file.path.has_extension() && file.path.extension() == ".dlg")
    {
      dialogue_files.push_back(file);
    }
  }
  return dialogue_files;
}
