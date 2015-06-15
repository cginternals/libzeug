
#pragma once


#include <reflectionzeug/type/PropertyBool.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyBool::PropertyBool(Args&&... args)
: AbstractPropertyValue<bool>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
