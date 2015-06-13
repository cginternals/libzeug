
#pragma once


#include <reflectionzeug/type/TypedFilePath.h>
#include <reflectionzeug/type/AbstractVisitor.h>


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

void TypedFilePath::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedFilePath>(this);
}


} // namespace reflectionzeug
