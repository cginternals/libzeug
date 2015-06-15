
#pragma once


#include <reflectionzeug/type/PropertyString.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyString::PropertyString(Args&&... args)
: AbstractPropertyValue<std::string>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
