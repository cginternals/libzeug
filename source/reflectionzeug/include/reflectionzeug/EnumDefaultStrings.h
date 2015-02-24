#pragma once

#include <map>
#include <string>

namespace reflectionzeug
{

/**
 * \brief Specialize this template to provide default string mapping for an enum.
 * Specialized templates should return an immutable map.
 */
template <typename Enum>
struct EnumDefaultStrings
{
    const std::map<Enum, std::string> & operator()()
    {
        static std::map<Enum, std::string> enumMap;
        return enumMap;
    }
};

} // namespace reflectionzeug

