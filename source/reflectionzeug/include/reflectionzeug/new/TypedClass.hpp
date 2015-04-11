
#pragma once


#include <iostream>
#include <reflectionzeug/new/TypedClass.h>
#include <reflectionzeug/new/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
TypedClass<T>::TypedClass(Args&&... args)
: AbstractTyped<T>(std::forward<Args>(args)...)
{
}

template <typename T>
TypedClass<T>::~TypedClass()
{
}

template <typename T>
std::string TypedClass<T>::toString() const
{
    return this->getValue().toString();
}

template <typename T>
bool TypedClass<T>::fromString(const std::string & string)
{
    bool ok;
    T value = T::fromString(string, &ok);

    if (!ok) {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }

    this->setValue(value);
    return true;
}

template <typename T>
void TypedClass<T>::accept(AbstractVisitor * visitor)
{
    // Call visitor->visit(TypedClass<T>)
    auto * typedVisitor = visitor->asVisitor<TypedClass<T>>();
    if (typedVisitor) {
        typedVisitor->visit(this);
    }
}


} // namespace reflectionzeug
