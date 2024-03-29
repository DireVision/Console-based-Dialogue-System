#include "dialogue_manager.h"

#include "dlg_parser.h"
#include "display.h"

// static member initialization
Document DialogueManager::current_dialogue;
std::vector<File> DialogueManager::dialogue_files;

std::vector<std::string> DialogueManager::dialogue_names;
std::vector<DialogueNode> DialogueManager::dialogue_nodes;

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

void DialogueManager::LoadDialogue(const std::filesystem::path& path)
{
  current_dialogue = DLG::Parse(path);
}

void DialogueManager::StartDialogue()
{
  // get names
  dialogue_names.clear();
  dialogue_names.push_back(player_name);
  ASSERT(current_dialogue.HasMember("speakers"), "Error: Dialogue has no speakers.");
  ASSERT(current_dialogue["speakers"].IsArray(), "Error: Speakers is not an array.");

  const Value& speakers = current_dialogue["speakers"];
  for (SizeType i = 0; i < speakers.Size(); i++)
  {
    ASSERT(speakers[i].IsString(), "Error: Speaker name is not a string.");
    dialogue_names.push_back(speakers[i].GetString());
  }

  // parse all nodes
  dialogue_nodes.clear();
  ASSERT(current_dialogue.HasMember("dialogue"), "Error: Dialogue has no dialogue nodes.");
  ASSERT(current_dialogue["dialogue"].IsArray(), "Error: Dialogue nodes is not an array.");

  const Value& dialogue = current_dialogue["dialogue"];

  if (dialogue.Empty())
  {
    std::cout << " No dialogue nodes found in the current dialogue.\n";
    return;
  }

  for (SizeType i = 0; i < dialogue.Size(); i++)
  {
    dialogue_nodes.push_back(DialogueNode(dialogue[i]));
  }
}

bool DialogueManager::Play()
{
  // display dialogue
  // if it's not a dialogue option, check next node
  // if next node is a dialogue option, keep appending nodes until it's not a dialogue option
  // then jump to the specified index and continue displaying dialogue
  // else, display the dialogue and wait for input
  int cached_index = 0; // for rolling back to the previous screen
  for (int i = 0; i < dialogue_nodes.size();)
  {
    const DialogueNode& node = dialogue_nodes[i];
    bool is_dialogue_option = node.IsDialogueOption();

    bool is_next_dialogue_option = false;

    // if there's a next node
    if (static_cast<size_t>(i) + 1 < dialogue_nodes.size())
    {
      is_next_dialogue_option = dialogue_nodes[i + 1].IsDialogueOption();
    }
    else
    {
      is_next_dialogue_option = false;
    }

    // regular dialogue, print node and check next node
    if (!is_dialogue_option)
    {
      ClearScreen();
      Screen::Title();

      // print node
      if (node.GetSpeakerIndex() < 0)
      {
        // narrator
        std::cout << " (" << node.GetText() << ")\n\n";
      }
      else
      {
        std::cout
          << "    " << std::string(dialogue_names[node.GetSpeakerIndex()].length() + 6, '-') << "\n"
          << "    |  " << dialogue_names[node.GetSpeakerIndex()] << "  |\n"
          << "    " << std::string(dialogue_names[node.GetSpeakerIndex()].length() + 6, '-') << "\n"
          << "\n"
        ;
        std::cout << TextWrapper(node.GetText()) << "\n";
        std::cout << "\n\n";
      }

#ifdef _DEBUG
      std::cout << "node: " << i << " | rollback: " << cached_index << "\n";
#endif

      // stop if next node is regular dialogue
      if (!is_next_dialogue_option)
      {
        // press any key
        Prompt::PressAnyKeyToContinue();
        if (WaitForInput()) return true;

        // jump to the specified index
        i = dialogue_nodes[i].GetGotoIndex();
        if (i < 0) return false; // end of dialogue
        cached_index = i;
      }
      // keep appending nodes until it's not a dialogue option
      else
      {
        cached_index = i++;
      }
    }
    // dialogue option
    else
    {
      // print option node
      std::cout
        << " [" << node.GetDialogueOptionIndex() << "] " << node.GetText() << "\n"
      ;

#ifdef _DEBUG
      std::cout << "option node: " << i << " | rollback: " << cached_index << "\n";
#endif

      // stop if next node is regular dialogue
      if (!is_next_dialogue_option)
      {
        // get option
        Prompt::PickADialogueOption();
        int option = 0;
        try
        {
          option = SelectOption(node.GetDialogueOptionIndex());
        }
        catch (const std::exception& e)
        {
          std::cout << e.what();
          Prompt::PressAnyKeyToContinue();
          if (WaitForInput()) return true;
          i = cached_index; // rollback and print the whole screen again
          continue;
        }

        if (option == 0) return true;
        else
        {
          // get the goto index from the selected node
          // the selected node's index is i - (max - option)
          int selected_node_index = i - (node.GetDialogueOptionIndex() - option);
          i = dialogue_nodes[selected_node_index].GetGotoIndex();
        }
      }
      // keep appending nodes until it's not a dialogue option
      else
      {
        i++;
      }
    }
  }
  
  return false;
}

void DialogueManager::EndDialogue()
{
  current_dialogue.SetNull();
  dialogue_files.clear();
  dialogue_names.clear();
  dialogue_nodes.clear();
}
