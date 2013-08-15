
#include <propertyzeug/FilePath.h>

namespace propertyzeug {

FilePath::FilePath()
:   m_string("")
{
}

FilePath::FilePath(const FilePath & filePath)
:   m_string(filePath.string())
{
}

FilePath::FilePath(const std::string & string)
:   m_string(string)
{
}
    
FilePath::FilePath(const char * string)
:   m_string(string)
{
}

FilePath::~FilePath()
{
}

const std::string & FilePath::string() const
{
    return m_string;
}

void FilePath::setString(const std::string & string)
{
    m_string = string;
}

} // namespace