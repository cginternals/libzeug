
#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug.h>


namespace reflectionzeug
{

namespace util
{

template <typename Type>
Type fromString(const std::string & string);

template <>
char fromString(const std::string & string);

template <>
unsigned char fromString(const std::string & string);

template <typename Type>
std::string toString(const Type & value);

template <>
std::string toString(const char & value);

template <>
std::string toString(const unsigned char & value);

template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator);

REFLECTIONZEUG_API bool matchesRegex(const std::string & string, const std::string & regex);

REFLECTIONZEUG_API std::vector<std::string> extract(const std::string & string, const std::string & regex);

REFLECTIONZEUG_API std::string trim(const std::string & string, bool enclosed = true);

REFLECTIONZEUG_API std::vector<std::string> splitArray(size_t size, const std::string & string);

} // namespace util

} // namespace reflectionzeug

#include "util.hpp"
