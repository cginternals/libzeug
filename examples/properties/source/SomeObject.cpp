
#include <propertyzeug/AbstractProperty.h>
#include "SomeObject.h"

const int & SomeObject::count() const
{
    return m_count;
}

void SomeObject::setCount(const int & count)
{
    m_count = count;
}

void SomeObject::propertyChanged(propertyzeug::AbstractProperty & property)
{
    std::cout << "Property changed with name = " << property.name() << std::endl;
}