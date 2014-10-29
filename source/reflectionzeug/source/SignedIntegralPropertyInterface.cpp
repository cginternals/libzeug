#include <reflectionzeug/SignedIntegralPropertyInterface.h>

#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

void SignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<SignedIntegralPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
