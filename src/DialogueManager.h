#pragma once
#include <string>
#include "DialogueNode.h" // For Node
#include <vector>
#include <utility>

class DialogueManager
{
public:
  void SetNewStory(std::vector<std::string> const& s, std::vector<Node> const& d);
  void SetPlayerName(std::string const& name);

  std::string GetDialogueOptions();
  std::pair<std::string, std::string> GetCurrentDialogue();
  bool SelectOption(int option);

  void IncrementIndex() { SetIndex(dialogues[index].next_node); }
  bool IsStoryDone() const { return index >= maxIndex; }

private:
  void SetIndex(int i) { index = (i == -1) ? maxIndex : i; } // If the goto is -1, story has terminated 

private:
  int index;
  int maxIndex;
  int num_options;
  std::string player_name;
  std::vector<std::string> speakers;
  std::vector<Node> dialogues;
};
