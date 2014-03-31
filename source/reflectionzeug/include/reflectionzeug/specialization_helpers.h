#pragma once

#include <array>
#include <type_traits>


namespace reflectionzeug
{
    
namespace
{

template <bool Condition, bool... MoreConditions>
struct all;

template <bool... MoreConditions>
struct all<true, MoreConditions...> : public all<MoreConditions...>
{
};

template <bool... MoreConditions>
struct all<false, MoreConditions...>
{
    enum { value = false };
};

template <>
struct all<true>
{
    enum { value = true };
};

template <>
struct all<false>
{
    enum { value = false };
};

template <bool Condition>
struct neg
{
    enum { value = true };
};

template <>
struct neg<true>
{
    enum { value = false };
};

template <typename Type>
struct is_array
{
    enum { value = false };
};

template <typename Type, size_t Size>
struct is_array<std::array<Type, Size>>
{
    enum { value = true };
};
    
template <typename Type, typename Container>
struct is_special_array
{
    enum { value = false };
};
    
template <typename Type, size_t Size>
struct is_special_array<Type, std::array<Type, Size>>
{
    enum { value = true };
};
    
}

template <typename Condition>
struct Neg : public neg<Condition::value> {};

template <typename... Conditions>
struct All : public all<Conditions::value...> {};

template <typename... Conditions>
struct EnableIf : std::enable_if<All<Conditions...>::value> {};

template <typename... Conditions>
struct DisableIf : public std::enable_if<!All<Conditions...>::value> {};

template <typename Type>
struct isArray : public is_array<Type> {};

template <typename Type>
struct isBoolArray : public is_special_array<bool, Type> {};

template <typename Type>
struct isIntArray : public is_special_array<int, Type> {};

template <typename Type>
struct isDoubleArray : public is_special_array<double, Type> {};
    
} // namespace reflectionzeug