#include <reflectionzeug/StringPropertyInterface.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

void StringPropertyInterface::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<StringPropertyInterface>();

    if (typedVisitor == nullptr)
        return AbstractValueProperty::accept(visitor);

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
