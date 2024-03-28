#include "dlg_parser.h"

#include <fstream>

namespace DLG
{
  Document Parse(const std::filesystem::path& file_path)
  {
    std::ifstream ifs(file_path);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);
    return doc;
  }
}