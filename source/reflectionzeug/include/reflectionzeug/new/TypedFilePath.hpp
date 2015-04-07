
#pragma once


#include <reflectionzeug/new/TypedFilePath.h>


namespace reflectionzeug
{


template <typename... Args>
TypedFilePath::TypedFilePath(Args&&... args)
: AbstractTyped<FilePath>(std::forward<Args>(args)...)
{
}

TypedFilePath::~TypedFilePath()
{
}


} // namespace reflectionzeug
