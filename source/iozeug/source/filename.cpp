
#include <iozeug/filename.h>


namespace
{
#ifdef WIN32
    const std::string g_sep = "\\";
#elif __APPLE__
    const std::string g_sep = "/";
#else
    const std::string g_sep = "/";
#endif
}


namespace iozeug
{


std::string getBaseName(const std::string & filePath)
{
    auto i = filePath.find_last_of(g_sep);

    std::string fileName = filePath;

    if (i == std::string::npos)
    {
        fileName = filePath.substr(++i);
    }

    while (fileName.length() > 0 && fileName[0] == '.') // note: filename might start with '.'
        fileName = fileName.substr(1);

    i = fileName.find_last_not_of(".");

    return i == fileName.npos ? fileName : fileName.substr(--i);
}

std::string getPath(const std::string & filePath)
{
    auto i = filePath.find_last_of(g_sep);
    return i == filePath.npos ? "" : filePath.substr(0, i);
}

std::string getExtension(const std::string & filename)
{
    // [TODO] What about .tar.gz? Maybe better use the first occurence, not the last?

    size_t pos = filename.find_last_of('.');

    if (pos == std::string::npos)
        return std::string();

    return filename.substr(pos+1);
}


} // namespace iozeug
