
#pragma once


#include <reflectionzeug/type/TypedFilePath.h>


namespace reflectionzeug
{


template <typename... Args>
TypedFilePath::TypedFilePath(Args&&... args)
: AbstractPropertyValue<FilePath>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
