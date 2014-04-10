
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

namespace reflectionzeug
{
    
UnsignedIntegralPropertyInterface::~UnsignedIntegralPropertyInterface()
{
}

void UnsignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<UnsignedIntegralPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
    {
        ValuePropertyInterface::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
