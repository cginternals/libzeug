
#pragma once


#include <reflectionzeug/property/PropertyString.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyString::PropertyString(Args&&... args)
: AbstractValueProperty<std::string>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
