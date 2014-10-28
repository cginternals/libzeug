#include <reflectionzeug/EnumPropertyInterface.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void EnumPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<EnumPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
