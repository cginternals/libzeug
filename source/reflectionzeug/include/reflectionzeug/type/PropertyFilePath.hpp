
#pragma once


#include <reflectionzeug/type/PropertyFilePath.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyFilePath::PropertyFilePath(Args&&... args)
: AbstractPropertyValue<FilePath>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
