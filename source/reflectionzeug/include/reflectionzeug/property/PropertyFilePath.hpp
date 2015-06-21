
#pragma once


#include <reflectionzeug/property/PropertyFilePath.h>


namespace reflectionzeug
{


template <typename... Args>
PropertyFilePath::PropertyFilePath(Args&&... args)
: AbstractTypedProperty<FilePath>(std::forward<Args>(args)...)
{
}


} // namespace reflectionzeug
