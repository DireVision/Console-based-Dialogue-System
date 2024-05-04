/*
* JSON is formatted in this way. Speakers is an array of strings.
* Dialogue is an array of arrays, each containing 4 key value pairs.
* When speaker is -1, it means that there should be no speaker text displayed as no one is speaking. Else it
* corresponds to the speaker list index + 1.
* Option 0 means the player does not get to choose and can only press proceed
* Else if it is any other value, it corresponds to one of many buttons that can be pressed.
* These will appear in continuous order, which will belong to the same scene.
* Goto refers to what index in the entire array to jump to. Reading -1 means the game is over.
*/
#include "DialogueReader.h"

#include <fstream>  // Reading in dialogue files

#include <rapidjson/istreamwrapper.h>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

void DialogueReader::Load(const char* filepath)
{
  // Opens a file stream and wraps it into rapidjson
  std::ifstream ifs(filepath);
  rapidjson::IStreamWrapper isw(ifs);
  d.ParseStream(isw);

  // Asserts that speakers and the json is a valid object.
  assert(d.IsObject() && "An invalid dlg file was read.");
  assert(d.HasMember("speakers") && d["speakers"].IsArray() && "Unrecognized DLG format");
}

std::vector<std::string> DialogueReader::GetSpeakers() const
{
  std::vector<std::string> speakers;

  // Reads speakers
  rapidjson::GenericArray<true, rapidjson::Value> speaker_array = d["speakers"].GetArray();

  for (auto a = speaker_array.Begin(); a != speaker_array.End(); ++a)
  {
    speakers.push_back(a->GetString());
  }

  return speakers;
}
  
std::vector<Node> DialogueReader::GetDialogues() const
{
  std::vector<Node> dialogues;

  // Reads dialogues
  rapidjson::GenericArray<true, rapidjson::Value> dialogue_array = d["dialogue"].GetArray();

  assert(dialogue_array[0].IsObject()); // Dialogue is an object...

  for (auto a = dialogue_array.Begin(); a != dialogue_array.End(); ++a)
  {
    // Check if it is a object
    assert(a->IsObject());

    rapidjson::GenericObject<true, rapidjson::Value> inner_object = a->GetObject();

    // Check for illegal members
    /*assert(inner_object.HasMember("option"),
      inner_object.HasMember("speaker"),
      inner_object.HasMember("text"),
      inner_object.HasMember("goto"));*/

    dialogues.push_back(Node{inner_object["option"].GetInt(),
                             inner_object["speaker"].GetInt(),
                             inner_object["text"].GetString(),
                             inner_object["goto"].GetInt() });

  }

  return dialogues;
}
