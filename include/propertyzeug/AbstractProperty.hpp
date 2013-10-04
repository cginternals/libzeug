
#pragma once

namespace zeug 
{
    
template <class Property>
Property * AbstractProperty::to()
{
    Property * property = dynamic_cast<Property *>(this);
    assert(property);
    return property;
}

template <class Property>
const Property * AbstractProperty::to() const
{
    const Property * property = dynamic_cast<const Property *>(this);
    assert(property);
    return property;
}

} // namespace zeug
