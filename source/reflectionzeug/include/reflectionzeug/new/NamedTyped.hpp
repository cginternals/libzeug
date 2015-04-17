
#pragma once


#include <reflectionzeug/new/NamedTyped.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
NamedTyped<T>::NamedTyped(const std::string & name, Args&&... args)
: Typed<T>(std::forward<Args>(args)...)
, m_name(name)
{
}

template <typename T>
NamedTyped<T>::~NamedTyped()
{
}

template <typename T>
std::string NamedTyped<T>::name() const
{
    return m_name;
}

template <typename T>
bool NamedTyped<T>::setName(const std::string & name)
{
    m_name = name;
    return true;
}


} // namespace reflectionzeug
