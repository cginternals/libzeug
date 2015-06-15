
#pragma once


#include <reflectionzeug/type/TypedColor.h>


namespace reflectionzeug
{


template <typename... Args>
TypedColor::TypedColor(Args&&... args)
: AbstractPropertyValue<Color>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
