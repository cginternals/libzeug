
#include <typeinfo>
#include <iostream>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/PropertyCategoryVisitor.h>


namespace reflectionzeug
{

bool AbstractValueProperty::isValue() const
{
    return true;
}

void AbstractValueProperty::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<AbstractValueProperty> *>(visitor);

    if (typedVisitor == nullptr)
    {
        if (warn)
            std::cout << "No method found for \"" << typeid(this).name() << "\"" << std::endl;
        return;
    }

    typedVisitor->visit(this);
}

} // namespace reflectionzeug
