#include <reflectionzeug/StringPropertyInterface.h>

#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

void StringPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<StringPropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
