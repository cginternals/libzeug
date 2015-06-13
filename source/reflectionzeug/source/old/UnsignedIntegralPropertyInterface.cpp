#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void UnsignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<UnsignedIntegralPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
