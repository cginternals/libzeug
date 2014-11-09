#include <reflectionzeug/SignedIntegralPropertyInterface.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void SignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<SignedIntegralPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
