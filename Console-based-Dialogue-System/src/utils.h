#pragma once

#include <conio.h> // _getch
#pragma warning(disable : 6031) // disable warning C6031: Return value ignored: '_getch'
#include <iostream>

#include <assert.h>
#define ASSERT(CHECK, MESSAGE) assert(CHECK && MESSAGE)

#include <exception>

#include <string>
#include <vector>
#include <filesystem>

extern bool g_running;
void Exit();

class Exception_Input_NaN : public std::exception
{
  std::string message;
public:
  Exception_Input_NaN(const std::string& message) : message(message) {}
  const char* what() const noexcept override { return message.c_str(); }
};

class Exception_Input_OutOfRange : public std::exception
{
  std::string message;
public:
  Exception_Input_OutOfRange(const std::string& message) : message(message) {}
  const char* what() const noexcept override { return message.c_str(); }
};

void PressAnyKeyToContinue();
int SelectDialogueOption(int max = 9);
void ClearScreen();
