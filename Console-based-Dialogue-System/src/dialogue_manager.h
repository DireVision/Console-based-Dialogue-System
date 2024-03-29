#pragma once

#include "utils.h"

#include "file.h"
#include "dialogue_node.h"

using namespace Engine;

class DialogueManager
{
  static Document current_dialogue;
  static std::vector<File> dialogue_files;

  static std::vector<std::string> dialogue_names;
  static std::vector<DialogueNode> dialogue_nodes;

public:
  static std::vector<File>& GetDialogueFiles() { return dialogue_files; }
  static Document& GetCurrentDialogue() { return current_dialogue; }
  static std::vector<std::string>& GetDialogueNames() { return dialogue_names; }

  static std::vector<File>& FilterDialogueFiles(const std::vector<File>& files);

  static void LoadDialogue(const std::filesystem::path& path);

  static void StartDialogue();
  static bool Play();
  static void EndDialogue();
};
