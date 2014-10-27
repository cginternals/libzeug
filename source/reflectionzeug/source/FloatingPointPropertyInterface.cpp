#include <reflectionzeug/FloatingPointPropertyInterface.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void FloatingPointPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<FloatingPointPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
