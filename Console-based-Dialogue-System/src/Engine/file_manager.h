#pragma once

#include "utils.h"
#include "file.h"

namespace Engine
{

  class FileManager
  {
    static std::filesystem::path current_directory;
    std::vector<File> files;

  public:
    // getters
    static std::filesystem::path GetCurrentDirectory() { return current_directory; }
    static std::filesystem::path GetDirectory(std::string& path) { return current_directory / path; }
    const std::vector<File>& GetFiles() const { return files; }
  
    const std::vector<File>& Load(std::filesystem::path& directory);
    const std::vector<File>& Load(std::string& path);
    const std::vector<File>& Load(const char* path);

    static std::filesystem::path Browse();

    // for debugging purposes
    std::string Dump();
  };

}
