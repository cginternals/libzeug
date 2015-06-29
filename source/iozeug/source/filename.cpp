
#include <iozeug/filename.h>


namespace iozeug
{


std::string getExtension(const std::string & filename)
{
    // [TODO] What about .tar.gz? Maybe better use the first occurence, not the last?

    size_t pos = filename.find_last_of('.');

    if (pos == std::string::npos)
        return std::string();

    return filename.substr(pos+1);
}


} // namespace iozeug
