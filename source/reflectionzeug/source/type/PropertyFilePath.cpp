
#include <reflectionzeug/type/PropertyFilePath.h>

#include <reflectionzeug/type/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyFilePath::~PropertyFilePath()
{
}

void PropertyFilePath::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyFilePath>(this);
}


} // namespace reflectionzeug
