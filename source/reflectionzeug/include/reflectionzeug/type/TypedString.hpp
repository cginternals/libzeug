
#pragma once


#include <reflectionzeug/type/TypedString.h>


namespace reflectionzeug
{


template <typename... Args>
TypedString::TypedString(Args&&... args)
: AbstractPropertyValue<std::string>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
