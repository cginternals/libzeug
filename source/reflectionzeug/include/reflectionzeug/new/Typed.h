
#pragma once


#include <reflectionzeug/new/TypedImpl.h>


namespace reflectionzeug
{


/**
*  @brief
*    Typed value (read/write)
*/
template <typename Type>
class Typed : public TypedImpl<Type>
{
public:
    Typed();

    Typed(std::function<Type ()> getter,
          std::function<void(const Type &)> setter);

    template <class Object>
    Typed(Object * object,
          const Type & (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    Typed(Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    Typed(Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(Type));

    Typed(Accessor<Type> * accessor);

    virtual ~Typed();
};


/**
*  @brief
*    Typed value (read-only)
*/
template <typename Type>
class Typed<const Type> : public TypedImpl<Type>
{
public:
    Typed();

    Typed(std::function<Type ()> getter);

    template <class Object>
    Typed(Object * object, const Type & (Object::*getter_pointer)() const);

    template <class Object>
    Typed(Object * object, Type (Object::*getter_pointer)() const);

    Typed(Accessor<const Type> * accessor);

    virtual ~Typed();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Typed.hpp>
