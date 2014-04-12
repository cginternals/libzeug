
#include <typeinfo>
#include <iostream>

#include <reflectionzeug/PropertyCategoryVisitor.h>
#include <reflectionzeug/ValuePropertyInterface.h>

namespace reflectionzeug
{

ValuePropertyInterface::ValuePropertyInterface()
:   AbstractProperty(std::string())
{
}
    
ValuePropertyInterface::ValuePropertyInterface(const std::string & name)
:   AbstractProperty(name)
{
}

void ValuePropertyInterface::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyCategoryVisitor<ValuePropertyInterface> *>(visitor);

    if (typedVisitor == nullptr)
    {
        if (warn)
            std::cout << "No method found for \"" << typeid(this).name() << "\"" << std::endl;
        return;
    }

    typedVisitor->visit(this);
}

bool ValuePropertyInterface::isArray() const
{
    return false;
}

} // namespace reflectionzeug
