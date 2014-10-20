#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

void UnsignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<UnsignedIntegralPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
