/*
  The job of the dialogue manager is to determine what should be displayed on screen
  Additionally it should be able to determine if there 
*/

#include "DialogueManager.h"
#include <iostream>
#include <sstream>

/// <summary>
/// Checks, generates and returns options text if there are options available. Else returns empty string
/// </summary>
/// <returns></returns>
std::string DialogueManager::GetDialogueOptions()
{
  std::stringstream ss;
  num_options = 0;

  // Check if next dialogue is an option
  if (index + 1 < maxIndex && dialogues[index + 1].option > 0)
  {
    ss << "\n\n\n\n"; // Spacing to separate options from the main dialogue text
    for (int x{ index + 1 }; x < maxIndex && dialogues[x].option > 0; ++x)
    {
      ss << "[" << dialogues[x].option << "]  " << dialogues[x].text << '\n';
      ++num_options;
    }
  }

  return ss.str();
}

/// <summary>
/// Tries to select an option and returns true if the option is valid
/// </summary>
/// <param name="option"> Option starting from 1 (No 0) </param>
/// <returns></returns>
bool DialogueManager::SelectOption(int option)
{
  if (option - 1 <= num_options)
  {
    SetIndex(dialogues[index + option].next_node);
    return true;
  }
  else 
    return false;
}

void DialogueManager::SetNewStory(std::vector<std::string> const& s, std::vector<Node> const& d)
{
  speakers = s;
  dialogues = d;
  index = 0;
  maxIndex = static_cast<int>(d.size());
}

void DialogueManager::SetPlayerName(std::string const& name)
{
  player_name = name;
}

/// <summary>
/// Gets the current dialogue and returns it as a pair of speaker and dialogue text
/// </summary>
/// <returns></returns>
std::pair<std::string, std::string> DialogueManager::GetCurrentDialogue()
{
  std::pair<std::string, std::string> speaker_dialogue_pair;

  speaker_dialogue_pair.first = dialogues[index].speaker - 1 < 0 ? "" : speakers[dialogues[index].speaker - 1];
  if (dialogues[index].speaker == 0) // If speaker is 0, it is the player
    speaker_dialogue_pair.first = player_name;
  speaker_dialogue_pair.second = dialogues[index].text + "\n";

  return speaker_dialogue_pair;
}