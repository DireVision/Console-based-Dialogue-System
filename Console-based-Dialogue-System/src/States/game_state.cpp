#include "game_state.h"

#include "file_manager.h"
using namespace Engine;

#include "dlg_parser.h"
#include "document.h"

FileManager files;

void GameState::OnEnter()
{
  std::cout << "GameState::OnEnter()" << std::endl;
//  files.Load("assets");
//
//  // parse .dlg files
//  for (const File& file : files.GetFiles())
//  {
//    auto doc = DLG::Parse(file.path);
//#ifdef _DEBUG
//    std::cout << " Parsed " << file.name << ".dlg\n";
//#endif
//  }
}

void GameState::OnExit()
{
  std::cout << "GameState::OnExit()" << std::endl;
}

void GameState::Update(float dt)
{
}

void GameState::Draw(float dt)
{
}
