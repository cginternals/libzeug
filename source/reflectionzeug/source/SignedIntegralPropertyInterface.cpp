
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/SignedIntegralPropertyInterface.h>

namespace reflectionzeug
{
    
SignedIntegralPropertyInterface::~SignedIntegralPropertyInterface()
{
}

void SignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<SignedIntegralPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
