
#include <reflectionzeug/type/TypedFilePath.h>

#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


TypedFilePath::~TypedFilePath()
{
}

void TypedFilePath::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<TypedFilePath>(this);
}


} // namespace reflectionzeug
