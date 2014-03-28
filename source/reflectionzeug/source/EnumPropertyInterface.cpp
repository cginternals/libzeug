
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/EnumPropertyInterface.h>

namespace reflectionzeug
{
    
EnumPropertyInterface::~EnumPropertyInterface()
{
}

void EnumPropertyInterface::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<EnumPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
    {
        ValuePropertyInterface::accept(visitor, warn);
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
