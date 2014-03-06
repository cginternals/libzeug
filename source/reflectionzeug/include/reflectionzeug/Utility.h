
#pragma once

#include <string>
#include <vector>


namespace reflectionzeug
{

template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator);

bool matchesRegex(const std::string & string, const std::string & regex);

std::vector<std::string> extract(const std::string & string, const std::string & regex);

} // namespace reflectionzeug

#include "Utility.hpp"
