
#pragma once

#include <string>


namespace reflectionzeug
{

template <class Iterable>
std::string join(const Iterable & iterable, const std::string & separator);

} // namespace reflectionzeug

#include "Utility.hpp"
