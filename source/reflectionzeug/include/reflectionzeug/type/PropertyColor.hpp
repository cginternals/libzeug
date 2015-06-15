
#pragma once


#include <reflectionzeug/type/PropertyColor.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyColor::PropertyColor(Args&&... args)
: AbstractPropertyValue<Color>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
