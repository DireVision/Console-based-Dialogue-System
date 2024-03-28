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
    // Initialize a BROWSEINFO structure
    BROWSEINFO bi = { 0 };
    bi.lpszTitle = L"Select a directory";
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    // Convert the item ID list to a path
    wchar_t path[MAX_PATH];
    if (pidl != nullptr) {
      SHGetPathFromIDList(pidl, path);
      CoTaskMemFree(pidl);
    }

    // Output the selected directory
    std::wcout << L"Selected directory: " << path << std::endl;

    return path;
  }

}
