#include <conio.h> // _getch
#pragma warning(disable : 6031) // disable warning C6031: Return value ignored: '_getch'
#define RAPIDJSON_NOMEMBERITERATORCLASS // disable warning C4996: 'std::_Iterator_base0': warning STL4015: The std::iterator_base class was deprecated in C++17. It is slated to be removed in a future version of C++.

#include <iostream>
#include <vector>
#include <iomanip>
#include "DialogueReader.h"
#include "DialogueManager.h"
#include "DisplayManager.h"

// For file reading menu
#include <Windows.h>
#include <filesystem>

// Managers
DialogueReader reader;
DialogueManager dialogueManager;
DisplayManager displayManager;

// Super simple switch case GSM.
enum GameState
{
  MENU,
  GAME
};
GameState gameState = MENU;

// Function to check if 0 is pressed at any point in the game
int getch_withexitcheck()
{
  int character = _getch();
  if (character == '0') 
    exit(0);   // Exits immediately if 0 is pressed at any point in the game.
  else 
    return character;
}

int main()
{
  #pragma region Initializing file open window
  // Load dialogue from file using windows explorer
  OPENFILENAME ofn;       // common dialog box structure
  wchar_t szFile[260];       // buffer for file name
  HWND hwnd = NULL;              // owner window
  HANDLE hf;              // file handle

  // Initialize OPENFILENAME
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = hwnd;
  ofn.lpstrFile = szFile;

  //
  // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
  // use the contents of szFile to initialize itself.
  //
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = L"dlg file (*.dlg)\0*.dlg\0"; // File enforcement - Only dlg files. Interestingly, the "(*dlg)" part is the one that controls this
  ofn.nFilterIndex = 1;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
#pragma endregion

  #pragma region Menu Screen
  displayManager.PrintToScreen("(12 char limit)\nEnter your name: ");

  int character{};
  std::string name;

  std::cin >> name;
  dialogueManager.SetPlayerName(name);
  system("cls"); 
#pragma endregion
  
  bool validInput = false; 
  while (!validInput)
  {
    switch (gameState)
    {
    case MENU:
      if (name != "")
        displayManager.PrintToScreen(" >>> Logged in as : " + name + "!<<<\n\n");
      else displayManager.PrintToScreen("");

      displayManager.PrintWithoutMenu("[1] Pick a dialogue from the assets folder\n[2] Load dialogue from file\n[3] Quit\n\nPick a menu option...\n");

      character = getch_withexitcheck();

      if (character == '1')
      {
        // Clear and reprint without the previous options.
        system("cls");
        if (name != "")
          displayManager.PrintToScreen(" >>> Logged in as : " + name + "!<<<\n\n");
        else displayManager.PrintToScreen("");

        // Get all files in the assets folder
        std::filesystem::path filePath("assets");

        // Show them as options
        int i{ 1 };
        std::vector<std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(filePath))
        {
          displayManager.PrintWithoutMenu('[' + std::to_string(i) + "] " + entry.path().filename().string() + '\n');
          ++i;
          files.push_back(entry.path().filename().string());
        }

        // Pause for file select
        character = getch_withexitcheck();

        if (character >= '1' && character < '9') 
        {
          int option = character - '1';
          if (option < files.size()) // Valid option was chosen
          {
            reader.Load(("assets/" + files[option]).c_str());
            dialogueManager.SetNewStory(reader.GetSpeakers(), reader.GetDialogues());

            gameState = GAME; 
          }
          else
          {
            if (option > '0' && option < '9')
              displayManager.PrintWithoutMenu("Invalid input: [" + std::to_string(character) + "] is not a valid option\n\nPress any key to continue...\n");
            else 
              displayManager.PrintWithoutMenu("Invalid input: Not a number\n\nPress any key to continue...\n");
            
            getch_withexitcheck();
          }
        }
        else
        {
          displayManager.PrintWithoutMenu("Invalid input: Not a number\n\nPress any key to continue...\n");
          getch_withexitcheck();
        }
      }
      else if (character == '2')
      {
        // Display the Open dialog box. 
        if (GetOpenFileName(&ofn) == TRUE)
        {
          hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
            0, (LPSECURITY_ATTRIBUTES)NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
            (HANDLE)NULL);

          // Load the file if there is one
          std::filesystem::path filePath = ofn.lpstrFile;
          reader.Load(filePath.string().c_str());

          dialogueManager.SetNewStory(reader.GetSpeakers(), reader.GetDialogues());

          gameState = GAME;
        }
      }
      else if (character == '3')
      {
        return 0;
      }
      else
      {
        displayManager.PrintWithoutMenu("Invalid input: Not a number.\n\n Press any key to continue...\n");
        getch_withexitcheck();
      }

      system("cls"); // clear the screen
      break;

    case GAME:
      if (dialogueManager.IsStoryDone())
      {
        gameState = MENU;
      }
      else
      {
        std::pair<std::string, std::string> dialogue_pair = dialogueManager.GetCurrentDialogue();
        displayManager.PrintDialogue(dialogue_pair);

        std::string options = dialogueManager.GetDialogueOptions();
        if (options != "")
        {
          displayManager.PrintWithoutMenu(options);
          character = getch_withexitcheck();

          bool result = dialogueManager.SelectOption(character - '0');
          if (!result)
          {
            displayManager.PrintWithoutMenu("Invalid option. Press any key to continue...\n");
            getch_withexitcheck();

          }
        }
        else
        {
          getch_withexitcheck();
          dialogueManager.IncrementIndex();
        }

        system("cls");
      }
      break;
    }
  }
}
