
#include <iozeug/FilePath.h>

#include <algorithm>


namespace iozeug
{


FilePath::FilePath()
: m_string("")
{
}

FilePath::FilePath(const FilePath & filePath)
: m_string(filePath.path())
{
}

FilePath::FilePath(const std::string & string)
: m_string(string)
{
}

FilePath::FilePath(const char * string)
: m_string(string)
{
}

FilePath::~FilePath()
{
}

FilePath FilePath::fromString(const std::string & string)
{    
    return FilePath(string);
}

const std::string & FilePath::path() const
{
    return m_string;
}

void FilePath::setPath(const std::string & path)
{
    m_string = path;
}

std::string FilePath::uniformPath() const
{
    auto copy = m_string;
    std::replace( copy.begin(), copy.end(), '\\', '/'); 
    return copy;
}

std::string FilePath::baseName() const
{
    auto path = this->uniformPath();
    auto i = path.find_last_of("/");

    if (i != std::string::npos)
    {
        path = path.substr(++i);
    }

    auto pos = path.find_first_of('.', 1); // Make sure the filename doesn't start with '.'

    if (pos == std::string::npos)
        return path;

    return path.substr(0, pos);
}

std::string FilePath::fileName() const
{
    auto path = this->uniformPath();
    auto i = path.find_last_of("/");

    if (i != std::string::npos)
    {
        path = path.substr(++i);
    }

    return path;
}

std::string FilePath::extension() const
{
    auto path = this->uniformPath();
    auto i = path.find_last_of("/");

    if (i != std::string::npos)
    {
        path = path.substr(++i);
    }

    auto pos = path.find_first_of('.', 1); // Make sure the filename doesn't start with '.'

    if (pos == std::string::npos)
        return std::string();

    return path.substr(++pos);
}

std::string FilePath::directoryPath() const
{
    auto path = this->uniformPath();
    auto pos = path.find_last_of("/");

    if (pos == std::string::npos)
        return std::string();

    return path.substr(0, pos+1); // Add trailing slash
}

std::string FilePath::driveLetter() const
{
    auto pos = m_string.find_first_of(":");

    if (pos == std::string::npos)
        return std::string();

    return m_string.substr(0, pos);
}


} // namespace iozeug
