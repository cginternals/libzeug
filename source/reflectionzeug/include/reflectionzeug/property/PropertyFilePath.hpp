
#pragma once


#include <reflectionzeug/property/PropertyFilePath.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyFilePath<T>::PropertyFilePath(Args&&... args)
: AbstractTypedProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyFilePath<T>::~PropertyFilePath()
{
}

template <typename T>
std::string PropertyFilePath<T>::toString() const
{
    return this->value().toString();
}

template <typename T>
bool PropertyFilePath<T>::fromString(const std::string & string)
{
    bool ok;
    FilePath value = FilePath::fromString(string, &ok);

    if (!ok)
    {
        printf("Could not read from string\n");
        return false;
    }

    this->setValue(value);
    return true;
}

template <typename T>
Variant PropertyFilePath<T>::toVariant() const
{
    // Return string variant
    return Variant(this->value().toString());
}

template <typename T>
bool PropertyFilePath<T>::fromVariant(const Variant & value)
{
    // Read from variant of the exact type
    if (value.hasType<T>() || value.canConvert<T>()) {
        this->setValue( value.value<T>() );
        return true;
    }

    // Read from string
    else if (value.hasType<std::string>() || value.canConvert<std::string>()) {
        fromString( value.value<std::string>() );
        return true;
    }

    // Invalid value
    return false;
}

template <typename T>
void PropertyFilePath<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyFilePath>(this);
}


} // namespace reflectionzeug
