#include <conio.h> // _getch
#pragma warning(disable : 6031) // disable warning C6031: Return value ignored: '_getch'
#include <iostream>

int main()
{
  std::cout << "Hello World!\n";
  _getch(); // wait for a key press
  system("cls"); // clear the screen
  std::cout << "Good luck with the project!\n";
}