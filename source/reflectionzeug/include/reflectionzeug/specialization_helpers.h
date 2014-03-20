
#pragma once

#include <type_traits>


namespace reflectionzeug
{

template <typename Condition>
using EnableIf = typename std::enable_if<Condition::value>::type;

template <typename Condition>
using DisableIf = typename std::enable_if<!Condition::value>::type;

} // namespace reflectionzeug
