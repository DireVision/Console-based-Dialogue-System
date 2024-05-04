#pragma once

#include <string>
#include <vector>

#define RAPIDJSON_NOMEMBERITERATORCLASS // disable warning C4996: 'std::_Iterator_base0': warning STL4015: The std::iterator_base class was deprecated in C++17. It is slated to be removed in a future version of C++.
#include "rapidjson/document.h"
#include "DialogueNode.h"

class DialogueReader
{
  public:
  DialogueReader() : d{ rapidjson::Document() }
  {
  }
  void Load(const char*);
  std::vector<std::string> GetSpeakers() const;
  std::vector<Node> GetDialogues() const;

  private:
  rapidjson::Document d;
};
