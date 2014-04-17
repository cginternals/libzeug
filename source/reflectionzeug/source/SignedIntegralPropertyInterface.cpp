
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/SignedIntegralPropertyInterface.h>

namespace reflectionzeug
{
    
SignedIntegralPropertyInterface::~SignedIntegralPropertyInterface()
{
}

void SignedIntegralPropertyInterface::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<SignedIntegralPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
    {
        AbstractValueProperty::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
