#include <reflectionzeug/AbstractValueProperty.h>

#include <typeinfo>
#include <iostream>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

bool AbstractValueProperty::isValue() const
{
    return true;
}

void AbstractValueProperty::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = visitor->asVisitor<AbstractValueProperty>();

    if (typedVisitor == nullptr)
    {
        std::cout << "No method found for \"" << typeid(this).name() << "\"" << std::endl;
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
