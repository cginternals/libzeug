
#pragma once


#include <reflectionzeug/type/TypedBool.h>


namespace reflectionzeug
{


template <typename... Args>
TypedBool::TypedBool(Args&&... args)
: AbstractPropertyValue<bool>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
