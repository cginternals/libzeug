
#pragma once

#include <type_traits>


namespace reflectionzeug
{

//template <typename Condition>
//using EnableIf = typename std::enable_if<Condition::value>::type;

template <typename Condition>
struct EnableIf_h : public std::enable_if<Condition::value> {};
    
template <typename Condition>
using EnableIf = typename EnableIf_h<Condition>::type;
    
//template <typename Condition>
//using DisableIf = typename std::enable_if<!Condition::value>::type;
    
template <typename Condition>
struct DisableIf_h : public std::enable_if<!Condition::value> {};

template <typename Condition>
using DisableIf = typename DisableIf_h<Condition>::type;

} // namespace reflectionzeug
