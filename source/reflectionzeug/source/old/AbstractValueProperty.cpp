#include <reflectionzeug/AbstractValueProperty.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

bool AbstractValueProperty::isValue() const
{
    return true;
}

void AbstractValueProperty::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<AbstractValueProperty>();

    if (typedVisitor == nullptr)
        return;

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
