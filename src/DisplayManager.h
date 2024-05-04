#pragma once

#include <string>
#include <iostream>

class DisplayManager
{
public:
  void PrintDialogue(std::pair<std::string, std::string> const& speaker_dialogue_pair);
  void PrintToScreen(std::string const& content);
  void PrintWithoutMenu(const std::string& content);

private:
  const std::string menu = R"(
  ||=============================================||
  ||        Console - based Dialogue System      ||
  ||            ~ Made by Yew Chong ~            ||
  ||                                             ||
  ||            Press [0] at any time            ||
  ||              to quit the game!              ||
  ||=============================================||)";

  std::string options;
};