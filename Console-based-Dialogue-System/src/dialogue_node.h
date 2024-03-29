#pragma once

#include "utils.h"

#include "document.h"
using namespace rapidjson;

class DialogueNode
{
  int option = 0;
  int speaker = -1;
  std::string text{};
  int goto_index = 0;

public:
  // special constructor to convert a rapidjson object to a DialogueNode
  DialogueNode(const Value& node)
  {
    ASSERT(node.IsObject(), "Error: DialogueNode is not an object.");

    ASSERT(node.HasMember("option"), "Error: DialogueNode missing option member.");
    ASSERT(node.HasMember("speaker"), "Error: DialogueNode missing speaker member.");
    ASSERT(node.HasMember("text"), "Error: DialogueNode missing text member.");
    ASSERT(node.HasMember("goto"), "Error: DialogueNode missing goto member.");

    ASSERT(node["option"].IsInt(), "Error: DialogueNode option member is not an integer.");
    ASSERT(node["speaker"].IsInt(), "Error: DialogueNode speaker member is not an integer.");
    ASSERT(node["text"].IsString(), "Error: DialogueNode text member is not a string.");
    ASSERT(node["goto"].IsInt(), "Error: DialogueNode goto member is not an integer.");
    
    option = node["option"].GetInt();
    speaker = node["speaker"].GetInt();
    text = node["text"].GetString();
    goto_index = node["goto"].GetInt();
  }

  int GetDialogueOptionIndex() const { return option; }
  int GetSpeakerIndex() const { return speaker; }
  const std::string& GetText() const { return text; }
  int GetGotoIndex() const { return goto_index; }
  bool IsDialogueOption() const { return option != 0; }

  void Dump() const
  {
    std::cout
      << " Dumping DialogueNode:\n"
      << " option: " << option << "\n"
      << " speaker: " << speaker << "\n"
      << " text: " << text << "\n"
      << " goto: " << goto_index << "\n"
    ;
  }
};
