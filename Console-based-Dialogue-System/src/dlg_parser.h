#pragma once

#include "utils.h"

#include "document.h"
#include "istreamwrapper.h"
using namespace rapidjson;

namespace DLG
{
  Document Parse(const std::filesystem::path& file_path);
}