
#pragma once


#include <reflectionzeug/type/NamedTyped.h>


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


} // namespace reflectionzeug
