#pragma once

#include "utils.h"

namespace Engine
{

  struct File
  {
    std::string name;
    std::filesystem::path path;

    File(const std::string& name, const std::filesystem::path& path)
      : name(name), path(path)
    {
    }

    std::string ToString() const
    {
      return " [ " + name + " ] " + path.string() + "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const File& file)
    {
      return os << file.path.filename().string() << "\n";
    }

    friend bool operator<(const File& lhs, const File& rhs) { return lhs.path < rhs.path; }
  };

}
