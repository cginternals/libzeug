#include <reflectionzeug/EnumPropertyInterface.h>

#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

void EnumPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<EnumPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
