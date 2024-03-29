#include "utils.h"

// extern
std::string player_name{};

void Quit()
{
  exit(0);
}

bool WaitForInput()
{
  return _getch() == '0';
}

int SelectOption(int max)
{
  int option = 0;

  char ch = _getch();

  // check if getch is 0
  if (ch == '0')
  {
    return 0;
  }
  // check if getch is a number
  else if (ch >= '1' && ch <= '9')
  {
    option = ch - '0';
  }
  else
  {
    throw Exception_Input_NaN(" Invalid input: Not a number.\n");
  }

  // check if the number is within the range
  if (option < 1 || option > max)
  {
    throw Exception_Input_OutOfRange(" Invalid input: [" + std::to_string(option) + "] is not a valid option.\n");
  }

  return option;
}

void ClearScreen()
{
  system("cls");
}

TextWrapper::TextWrapper(const std::string& text, size_t line_length)
{
  std::string current_line = " "; // indent
  int current_line_length = 1;
  auto it = text.begin();

  // iterate through the text
  while (it != text.end())
  {
    // look for the next space
    auto space = std::find(it, text.end(), ' ');

    // check if the line length exceeds the line length limit
    if (static_cast<size_t>(current_line_length + (space - it)) > line_length)
    {
      // new line
      lines.push_back(current_line);
      current_line.clear();
      current_line.push_back(' '); // indent
      current_line_length = 1;
    }

    // add the word to the current line
    current_line.append(it, space);
    current_line_length += static_cast<int>(space - it);

    // move the iterator to the next word
    it = space;

    // skip the space
    if (it != text.end())
    {
      ++it;
      current_line.push_back(' '); // add space
      ++current_line_length;
    }
  }

  // add the last line
  lines.push_back(current_line);
}

std::ostream& operator<<(std::ostream& os, const TextWrapper& wrapper)
{
  for (const auto& line : wrapper.lines)
  {
    os << line << "\n";
  }
  return os;
}
