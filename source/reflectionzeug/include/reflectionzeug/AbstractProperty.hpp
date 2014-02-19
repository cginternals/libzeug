
#pragma once

namespace reflectionzeug
{
    
template <class Property>
Property * AbstractProperty::as()
{
    Property * property = dynamic_cast<Property *>(this);
    assert(property);
    return property;
}

template <class Property>
const Property * AbstractProperty::as() const
{
    const Property * property = dynamic_cast<const Property *>(this);
    assert(property);
    return property;
}

} // namespace reflectionzeug
