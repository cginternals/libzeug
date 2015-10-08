
#pragma once


#include <reflectionzeug/property/PropertyVariant.h>
#include <reflectionzeug/property/AbstractVisitor.h>
#include <reflectionzeug/tools/JSONReader.h>

namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyVariant<T>::PropertyVariant(Args&&... args)
: AbstractTypedProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyVariant<T>::~PropertyVariant()
{
}

template <typename T>
std::string PropertyVariant<T>::toString() const
{
    return this->value().toJSON();
}

template <typename T>
bool PropertyVariant<T>::fromString(const std::string & string)
{
    JSONReader reader;
    Variant variant;
    
    if (reader.parse(string, variant))
    {
        this->setValue(variant);
        return true;
    }

    return false;
}

template <typename T>
void PropertyVariant<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyVariant<T>>(this);
    visitor->callVisitor<AbstractVariantInterface>(this);
}


} // namespace reflectionzeug
