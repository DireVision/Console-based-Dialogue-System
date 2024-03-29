#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "file_manager.h"
#include "dlg_parser.h"
#include "dialogue_manager.h"
#include "display.h"

using namespace Engine;

enum State
{
  STATE_TITLE = 0,
  STATE_MENU,
  STATE_DIALOGUE_PICKER,
  STATE_PLAY,
  STATE_EXIT,
  STATE_LAST
};

int main()
{
#ifdef _DEBUG
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  FileManager dialogue_file;
  Document current_dialogue;
  std::filesystem::path buffer_path;
  std::string buffer_string;
  int buffer_option = 0; // for option selection
  int buffer_count = 0;  // for option count
  int current_state = STATE_TITLE;

  while (true)
  {
    ClearScreen();
    Screen::Title();

    switch (current_state)
    {
    case STATE_TITLE:
      Prompt::PressStartToPlay();
      if (WaitForInput()) return 0;
      current_state = STATE_MENU;
      break;

    case STATE_MENU:
      Screen::MainMenu();
      Prompt::PickAMenuOption();

      try
      {
        buffer_option = SelectOption();
      }
      catch (const std::exception& e)
      {
        std::cout << e.what();
        Prompt::PressAnyKeyToContinue();
        if (WaitForInput()) return 0;
      }

      switch (buffer_option)
      {
      case 1:
        current_state = STATE_DIALOGUE_PICKER;
        break;
      case 2:
        buffer_path = FileManager::Browse();
        current_dialogue = DLG::Parse(buffer_path);
        current_state = STATE_PLAY;
        break;
      case 3:
      case 0:
        current_state = STATE_EXIT;
        break;
      }

      break;

    case STATE_DIALOGUE_PICKER:
      dialogue_file.Load("assets");
      DialogueManager::FilterDialogueFiles(dialogue_file.GetFiles());
      buffer_count = Screen::DisplayDlgFiles(DialogueManager::GetDialogueFiles());

      if (buffer_count == 0)
      {
        std::cout << " No dialogue files found in the assets folder.\n";
        Prompt::PressAnyKeyToContinue();
        if (WaitForInput()) return 0;
        current_state = STATE_MENU;
      }

      Prompt::PickAMenuOption();

      try
      {
        buffer_option = SelectOption(buffer_count);
        if (buffer_option == 0) return 0;
      }
      catch (const std::exception& e)
      {
        std::cout << e.what();
        Prompt::PressAnyKeyToContinue();
        if (WaitForInput()) return 0;
      }

      current_dialogue = DLG::Parse(DialogueManager::GetDialogueFiles()[buffer_option - 1].path);
      current_state = STATE_PLAY;
      break;

    case STATE_PLAY:
      buffer_string = current_dialogue.GetArray()[0].GetObject()["name"].GetString();
      std::cout << buffer_string;

      Prompt::PressAnyKeyToContinue();
      if (WaitForInput()) return 0;

      current_state = STATE_MENU;

      //DialogueManager::StartDialogue();
      break;
    case STATE_EXIT:
      return 0;
    }
  }

  return 0;
}