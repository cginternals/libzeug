
#pragma once


#include <reflectionzeug/property/PropertyColor.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyColor<T>::PropertyColor(Args&&... args)
: AbstractTypedProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyColor<T>::~PropertyColor()
{
}


template <typename T>
void PropertyColor<T>::getRGBA(int & r, int & g, int & b, int & a) const
{
    Color color = this->value();
    r = color.red();
    g = color.green();
    b = color.blue();
    a = color.alpha();
}

template <typename T>
void PropertyColor<T>::setRGBA(int r, int g, int b, int a)
{
    this->setValue(Color(r, g, b, a));
}

template <typename T>
int PropertyColor<T>::red() const
{
    return this->value().red();
}

template <typename T>
void PropertyColor<T>::setRed(int red)
{
    Color color = this->value();
    color.setRed(red);
    this->setValue(color);
}

template <typename T>
int PropertyColor<T>::green() const
{
    return this->value().green();
}

template <typename T>
void PropertyColor<T>::setGreen(int green)
{
    Color color = this->value();
    color.setGreen(green);
    this->setValue(color);
}

template <typename T>
int PropertyColor<T>::blue() const
{
    return this->value().blue();
}

template <typename T>
void PropertyColor<T>::setBlue(int blue)
{
    Color color = this->value();
    color.setBlue(blue);
    this->setValue(color);
}

template <typename T>
int PropertyColor<T>::alpha() const
{
    return this->value().alpha();
}

template <typename T>
void PropertyColor<T>::setAlpha(int alpha)
{
    Color color = this->value();
    color.setAlpha(alpha);
    this->setValue(color);
}

template <typename T>
std::string PropertyColor<T>::toString() const
{
    // Return hex representation
    return toHexString();
}

template <typename T>
bool PropertyColor<T>::fromString(const std::string & string)
{
    // Read from hex representation
    return fromHexString(string);
}

template <typename T>
Variant PropertyColor<T>::toVariant() const
{
    // Return color as variant object
    return toColorVariant();
}

template <typename T>
bool PropertyColor<T>::fromVariant(const Variant & value)
{
    // Read from variant of the exact type
    if (value.hasType<T>() || value.canConvert<T>()) {
        this->setValue( value.value<T>() );
        return true;
    }

    // Read from string or object representation
    else {
        return fromColorVariant(value);
    }
}

template <typename T>
void PropertyColor<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyColor>(this);
    visitor->callVisitor<AbstractColorInterface>(this);
}


} // namespace reflectionzeug
