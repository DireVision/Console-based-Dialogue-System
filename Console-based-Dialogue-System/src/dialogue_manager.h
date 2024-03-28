#pragma once

#include "utils.h"

#include "file_manager.h"
#include "dlg_parser.h"

#include "document.h"

class DialogueManager
{
  static Document current_dialogue;

public:
  static void LoadDialogue(const std::string& filename);
  static void StartDialogue();
  static void ContinueDialogue();
  static void EndDialogue();
  static void HandleInput();
  static void Update();
  static void Render();
  static void CleanUp();
};