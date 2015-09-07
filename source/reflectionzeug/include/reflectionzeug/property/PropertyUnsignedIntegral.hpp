
#pragma once


#include <reflectionzeug/property/PropertyUnsignedIntegral.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{

template <typename T>
bool setValueULL(PropertyUnsignedIntegral<T> & p, const unsigned long long v);

template <typename T>
bool setValueULL<T>(PropertyUnsignedIntegral<T> & p, const unsigned long long v)
{
	p.setValue(static_cast<T>(v));
	return true; // ToDo: this seems wrong! - why are there value setters returning void?
};

template <>
REFLECTIONZEUG_API bool setValueULL<bool>(PropertyUnsignedIntegral<bool> & p, const unsigned long long v);

template <>
REFLECTIONZEUG_API bool setValueULL<const bool>(PropertyUnsignedIntegral<const bool> & p, const unsigned long long v);


template <typename T>
template <typename... Args>
PropertyUnsignedIntegral<T>::PropertyUnsignedIntegral(Args&&... args)
: AbstractNumberProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyUnsignedIntegral<T>::~PropertyUnsignedIntegral()
{
}

template <typename T>
unsigned long long PropertyUnsignedIntegral<T>::toULongLong() const
{
    return static_cast<unsigned long long>(value());
}

template <typename T>
bool PropertyUnsignedIntegral<T>::fromULongLong(unsigned long long v)
{
	return setValueULL(*this, v);
}


template <typename T>
void PropertyUnsignedIntegral<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyUnsignedIntegral<T>>(this);
    visitor->callVisitor<AbstractUnsignedIntegralInterface>(this);
}

template <typename T>
std::string PropertyUnsignedIntegral<T>::matchRegex() const
{
    // Match an integral number
    return "\\+?\\d+";
}


} // namespace reflectionzeug
