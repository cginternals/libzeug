
#pragma once

#include <sstream>


namespace reflectionzeug
{

template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator)
{    
    std::stringstream stream;

    for (auto it = iterable.begin(); it != iterable.end(); ++it)
    {
        stream << *it;

        if (it != --iterable.end())
            stream << separator;
    }
    
    return stream.str();
}

} // namespace reflectionzeug
