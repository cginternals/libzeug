
#include <reflectionzeug/FilePath.h>

namespace reflectionzeug
{

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

FilePath FilePath::fromString(const std::string & string, bool * ok)
{
    *ok = true;
    
    return FilePath(string);
}

const std::string & FilePath::string() const
{
    return m_string;
}

void FilePath::setString(const std::string & string)
{
    m_string = string;
}

const std::string & FilePath::toString() const
{
    return m_string;
}

} // namespace reflectionzeug
