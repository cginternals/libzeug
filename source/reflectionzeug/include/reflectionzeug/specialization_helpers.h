
#pragma once

#include <type_traits>


namespace reflectionzeug
{

// Replace code below as soon as Visual Studio fully supports type aliases.

// template <typename Condition>
// using EnableIf = typename std::enable_if<Condition::value>::type;
   
// template <typename Condition>
// using DisableIf = typename std::enable_if<!Condition::value>::type;
    
template <typename Condition>
struct EnableIfHelper : public std::enable_if<Condition::value> {};
    
template <typename Condition>
using EnableIf = typename EnableIfHelper<Condition>::type;
    
template <typename Condition>
struct DisableIfHelper : public std::enable_if<!Condition::value> {};

template <typename Condition>
using DisableIf = typename DisableIfHelper<Condition>::type;

} // namespace reflectionzeug
