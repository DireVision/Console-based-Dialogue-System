#pragma once

#include "utils.h"

#include "file_manager.h"
#include "dlg_parser.h"

#include "document.h"

using namespace Engine;

class DialogueManager
{
  static Document current_dialogue;
  static std::vector<File> dialogue_files;

public:
  static std::vector<File>& GetDialogueFiles() { return dialogue_files; }

  static std::vector<File>& FilterDialogueFiles(const std::vector<File>& files);

  static void LoadDialogue(const std::string& filename);
  static void StartDialogue();
  static void ContinueDialogue();
  static void EndDialogue();
  static void HandleInput();
  static void Update();
  static void Render();
  static void CleanUp();
};