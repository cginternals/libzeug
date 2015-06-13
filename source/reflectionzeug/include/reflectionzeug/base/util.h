#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{

/**
 * \brief Utility methods which deal with common string conversion, 
 * string manipulation and regular expressions.
 */
namespace util
{

template <typename Type>
Type fromString(const std::string & string);

template <>
REFLECTIONZEUG_API char fromString<char>(const std::string & string);

template <>
REFLECTIONZEUG_API unsigned char fromString<unsigned char>(const std::string & string);

template <typename Type>
std::string toString(const Type & value);

template <>
REFLECTIONZEUG_API std::string toString<char>(const char & value);

template <>
REFLECTIONZEUG_API std::string toString<unsigned char>(const unsigned char & value);

template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator);

REFLECTIONZEUG_API bool matchesRegex(const std::string & string, const std::string & regex);

REFLECTIONZEUG_API std::vector<std::string> extract(const std::string & string, const std::string & regex);

REFLECTIONZEUG_API std::string trim(const std::string & string, bool enclosed = true);

REFLECTIONZEUG_API std::vector<std::string> splitArray(size_t size, const std::string & string);
    
REFLECTIONZEUG_API std::vector<std::string> split(const std::string & input, char delimiter);

} // namespace util

} // namespace reflectionzeug

#include <reflectionzeug/base/util.hpp>
