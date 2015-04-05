
#pragma once


#include <functional>

#include <reflectionzeug/new/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) via getter/setter functions
*/
template <typename Type>
class AccessorGetSet : public Accessor<Type>
{
public:
    AccessorGetSet(std::function<Type ()> getter,
                  std::function<void(const Type &)> setter);

    template <class Object>
    AccessorGetSet(Object * object,
                  const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AccessorGetSet(Object * object,
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));

    template <class Object>
    AccessorGetSet(Object * object,
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));

    virtual ~AccessorGetSet();

    virtual Type getValue() const override;
    virtual void setValue(const Type & value) override;


protected:
    std::function<Type ()>            m_getter;
    std::function<void(const Type &)> m_setter;
};


/**
*  @brief
*    Accessor (read-only) via getter/setter functions
*/
template <typename Type>
class AccessorGetSet<const Type> : public Accessor<const Type>
{
public:
    AccessorGetSet(std::function<Type ()> getter);

    template <class Object>
    AccessorGetSet(Object * object,
                  const Type & (Object::*getter_pointer)() const);

    template <class Object>
    AccessorGetSet(Object * object,
                  Type (Object::*getter_pointer)() const);

    virtual ~AccessorGetSet();

    virtual Type getValue() const override;


protected:
    std::function<Type ()> m_getter;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/AccessorGetSet.hpp>
