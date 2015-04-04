
#pragma once


#include <reflectionzeug/new/TypedFilePath.h>


namespace reflectionzeug
{


template <typename Accessor>
TypedFilePath<Accessor>::TypedFilePath(const Accessor & accessor)
: TypedBase<FilePath, Accessor>(accessor)
{
}

template <typename Accessor>
TypedFilePath<Accessor>::~TypedFilePath()
{
}


} // namespace reflectionzeug
