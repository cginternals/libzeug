
#include <reflectionzeug/property/PropertyFilePath.h>

#include <reflectionzeug/property/AbstractVisitor.h>


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
