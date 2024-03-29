#include "file_manager.h"

#include <windows.h>
#include <shlobj.h>

#include <fstream>
#include <sstream>

namespace Engine
{

  // static member initialization
  std::filesystem::path FileManager::current_directory = std::filesystem::current_path();

  const std::vector<File>& FileManager::Load(std::filesystem::path& directory)
  {
    // guard
    ASSERT(std::filesystem::exists(directory), "Directory does not exist!");

    // get all files in assets folder
    files.clear();
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
      files.push_back({ entry.path().stem().string(), entry.path() });
    }

    return GetFiles();
  }

  const std::vector<File>& FileManager::Load(std::string& path)
  {
    std::filesystem::path directory = GetDirectory(path);
    return Load(directory);
  }

  const std::vector<File>& FileManager::Load(const char* path)
  {
    std::string _path = path;
    return Load(_path);
  }

  std::string FileManager::Dump()
  {
    std::stringstream ss{ " FileManager::Dump()\n\n List of files: \n" };
    for (const File& file : files) ss << file;
    ss << "\n\n";
    return ss.str();
  }

  std::filesystem::path FileManager::Browse()
  {
    // Initialize OPENFILENAME structure
    OPENFILENAME ofn = { 0 };
    wchar_t file_name[MAX_PATH] = L"";

    std::wstring w_path = GetCurrentDirectoryPath().wstring();
    wchar_t initialDir[MAX_PATH];
    wcscpy_s(initialDir, w_path.c_str());

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = L"Dialog Files (*.dlg)\0*.dlg\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = file_name;
    ofn.lpstrTitle = L"Select a .dlg file";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

    // Show the dialog and get the selected file(s)
    if (GetOpenFileName(&ofn))
    {
      // Do something with the selected file(s)
      std::wcout << L"Selected file: " << file_name << std::endl;
    }

    return std::filesystem::path{ file_name };
  }

}
