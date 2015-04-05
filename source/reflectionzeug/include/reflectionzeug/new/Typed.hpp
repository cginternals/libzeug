
#pragma once


#include <reflectionzeug/new/Typed.h>
#include <reflectionzeug/new/AccessorValue.h>
#include <reflectionzeug/new/AccessorGetSet.h>


namespace reflectionzeug
{


// Read/write value
template <typename Type>
Typed<Type>::Typed()
: TypedImpl<Type>(new AccessorValue<Type>())
{
}

template <typename Type>
Typed<Type>::Typed(std::function<Type ()> getter,
	std::function<void(const Type &)> setter)
: TypedImpl<Type>(new AccessorGetSet<Type>(getter, setter))
{
}

template <typename Type>
template <class Object>
Typed<Type>::Typed(Object * object,
	const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: TypedImpl<Type>(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
Typed<Type>::Typed(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
: TypedImpl<Type>(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
template <class Object>
Typed<Type>::Typed(Object * object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
: TypedImpl<Type>(new AccessorGetSet<Type>(getter_pointer, setter_pointer))
{
}

template <typename Type>
Typed<Type>::Typed(Accessor<Type> * accessor)
: TypedImpl<Type>(accessor)
{
}

template <typename Type>
Typed<Type>::~Typed()
{
}


// Read-only value
template <typename Type>
Typed<const Type>::Typed()
: TypedImpl<Type>(new AccessorValue<const Type>())
{
}

template <typename Type>
Typed<const Type>::Typed(std::function<Type ()> getter)
: TypedImpl<Type>(new AccessorGetSet<const Type>(getter))
{
}

template <typename Type>
template <class Object>
Typed<const Type>::Typed(Object * object, const Type & (Object::*getter_pointer)() const)
: TypedImpl<Type>(new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
template <class Object>
Typed<const Type>::Typed(Object * object, Type (Object::*getter_pointer)() const)
: TypedImpl<Type>(new AccessorGetSet<const Type>(getter_pointer))
{
}

template <typename Type>
Typed<const Type>::Typed(Accessor<const Type> * accessor)
: TypedImpl<Type>(accessor)
{
}

template <typename Type>
Typed<const Type>::~Typed()
{
}


} // namespace reflectionzeug
