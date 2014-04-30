
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/EnumPropertyInterface.h>

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
