
#pragma once


#include <type_traits>

#include <reflectionzeug/base/util.h>

#include <sstream>


namespace reflectionzeug
{

namespace util
{


template <typename Type>
Type fromString(const std::string & string)
{
    std::stringstream stream(string);
    typename std::remove_const<Type>::type value;
    stream >> value;
    return value;
}

template <typename Type>
std::string toString(const Type & value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

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

    
} // namespace util

} // namespace reflectionzeug
