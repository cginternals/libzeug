
#pragma once


#include <memory>
#include <functional>

#include <reflectionzeug/new/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed values (read/write)
*/
template <typename Type>
class AbstractTyped
{
public:
    AbstractTyped();

    AbstractTyped(std::function<Type ()> getter,
          std::function<void(const Type &)> setter);

    template <class Object>
    AbstractTyped(Object * object,
          const Type & (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractTyped(Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AbstractTyped(Object * object,
          Type (Object::*getter_pointer)() const,
          void (Object::*setter_pointer)(Type));

    AbstractTyped(Accessor<Type> * accessor);

    virtual ~AbstractTyped();

    Type getValue() const;
    void setValue(const Type & value);


protected:
    std::unique_ptr<Accessor<Type>> m_accessor;
};


/**
*  @brief
*    Base class for typed values (read-only)
*/
template <typename Type>
class AbstractTyped<const Type> : public AbstractTyped<Type>
{
public:
    AbstractTyped();

    AbstractTyped(std::function<Type ()> getter);

    template <class Object>
    AbstractTyped(Object * object,
          const Type & (Object::*getter_pointer)() const);

    template <class Object>
    AbstractTyped(Object * object,
          Type (Object::*getter_pointer)() const);

    AbstractTyped(Accessor<const Type> * accessor);

    virtual ~AbstractTyped();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/AbstractTyped.hpp>
