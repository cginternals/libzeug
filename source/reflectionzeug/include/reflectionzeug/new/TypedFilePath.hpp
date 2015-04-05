
#pragma once


#include <reflectionzeug/new/TypedFilePath.h>


namespace reflectionzeug
{


TypedFilePath::TypedFilePath(Accessor<FilePath> * accessor)
: TypedBase<FilePath>(accessor)
{
}

TypedFilePath::~TypedFilePath()
{
}


} // namespace reflectionzeug
