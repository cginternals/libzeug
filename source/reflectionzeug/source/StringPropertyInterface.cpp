
#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/StringPropertyInterface.h>


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
