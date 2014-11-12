#include <reflectionzeug/ColorPropertyInterface.h>

#include <iostream>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void ColorPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<ColorPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
