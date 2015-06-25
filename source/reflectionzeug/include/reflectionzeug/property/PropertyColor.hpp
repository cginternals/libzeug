
#pragma once


#include <reflectionzeug/property/PropertyColor.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyColor::PropertyColor(Args&&... args)
: AbstractTypedProperty<Color>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
