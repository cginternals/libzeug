
#pragma once

#include <string>
#include <vector>


namespace reflectionzeug
{

namespace util
{

template <typename Type>
Type fromString(const std::string & string);

template <typename Type>
std::string toString(const Type & value);

template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator);

bool matchesRegex(const std::string & string, const std::string & regex);

std::vector<std::string> extract(const std::string & string, const std::string & regex);

std::string trim(const std::string & string);

} // namespace util

} // namespace reflectionzeug

#include "util.hpp"
