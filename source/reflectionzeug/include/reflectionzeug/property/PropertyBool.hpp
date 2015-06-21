
#pragma once


#include <reflectionzeug/property/PropertyBool.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyBool::PropertyBool(Args&&... args)
: AbstractTypedProperty<bool>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
