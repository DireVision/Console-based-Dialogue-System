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
      // get player name
      std::cout
        << " (12 char limit)\n"
        << " Enter your name: ";
      std::getline(std::cin, player_name, '\n');

      // input sanitization
      // remove any special characters
      player_name.erase(std::remove_if(player_name.begin(), player_name.end(), [](char c) { return !std::isalnum(c); }), player_name.end());
      // don't allow more than 12 characters
      if (player_name.length() > 12)
      {
        player_name = player_name.substr(0, 12);
      }

      current_state = STATE_MENU;
      break;

    case STATE_MENU:
      buffer_count = Screen::MainMenu();
      Prompt::PickAMenuOption();

      try
      {
        buffer_option = SelectOption(buffer_count);
      }
      catch (const std::exception& e)
      {
        std::cout << e.what();
        buffer_option = -1;
        Prompt::PressAnyKeyToContinue();
        if (WaitForInput()) Quit();
      }

      switch (buffer_option)
      {
      case 1:
        current_state = STATE_DIALOGUE_PICKER;
        break;
      case 2:
        buffer_path = FileManager::Browse();
        DialogueManager::LoadDialogue(buffer_path);
        current_state = STATE_PLAY;
        break;
      case 3:
      case 0:
        Quit();
        break;
      default:
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
        if (WaitForInput()) Quit();
        current_state = STATE_MENU;
      }

      Prompt::PickAMenuOption();

      try
      {
        buffer_option = SelectOption(buffer_count);
      }
      catch (const std::exception& e)
      {
        std::cout << e.what();
        buffer_option = -1;
        Prompt::PressAnyKeyToContinue();
        if (WaitForInput()) Quit();
      }

      if (buffer_option == 0)
      {
        Quit();
      }
      else if (buffer_option > 0 && buffer_option <= buffer_count)
      {
        DialogueManager::LoadDialogue(DialogueManager::GetDialogueFiles()[buffer_option - 1].path);
        current_state = STATE_PLAY;
      }
      break;

    case STATE_PLAY:
      DialogueManager::StartDialogue();
      if (DialogueManager::Play()) Quit();
      DialogueManager::EndDialogue();
      current_state = STATE_MENU;
      break;
    }
  }

  return 0;
}