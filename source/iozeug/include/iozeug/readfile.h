#pragma once

#include <string>

#include <iozeug/iozeug.h>

namespace iozeug 
{

// copied from glow::internal::FileReader
IOZEUG_API bool readFile(const std::string & filePath, std::string & content);
IOZEUG_API std::string readFile(const std::string & filePath);

} // namespace iozeug
