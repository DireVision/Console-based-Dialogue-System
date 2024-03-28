#include "dialogue_manager.h"

Document DialogueManager::current_dialogue;

//void DialogueManager::LoadDialogue(const std::string& filename)
//{
//  // load .dlg files
//  FileManager::Load();
//#ifdef _DEBUG
//  std::cout << FileManager::Dump();
//#endif
//
//  current_dialogue = DLG::Parse(FileManager::ReadFile(filename));
//
//
//}