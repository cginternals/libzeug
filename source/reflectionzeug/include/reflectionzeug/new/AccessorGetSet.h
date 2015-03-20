
#pragma once


#include <functional>

#include <reflectionzeug/new/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Accessor (read/write) via getter/setter functions
*/
template <typename T>
class AccessorGetSet : public Accessor<T>
{
public:
    AccessorGetSet(std::function<T ()> getter,
                  std::function<void(const T &)> setter);

    template <class Object>
    AccessorGetSet(Object * object,
                  const T & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const T &));

    template <class Object>
    AccessorGetSet(Object * object,
                  T (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const T &));

    template <class Object>
    AccessorGetSet(Object * object,
                  T (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(T));

    virtual ~AccessorGetSet();

    virtual T get() const override;
    virtual void set(const T & value) override;


protected:
    std::function<T ()>            m_getter;
    std::function<void(const T &)> m_setter;
};


/**
*  @brief
*    Accessor (read-only) via getter/setter functions
*/
template <typename T>
class AccessorGetSet<const T> : public Accessor<const T>
{
public:
    AccessorGetSet(std::function<T ()> getter);

    template <class Object>
    AccessorGetSet(Object * object,
                  const T & (Object::*getter_pointer)() const);

    template <class Object>
    AccessorGetSet(Object * object,
                  T (Object::*getter_pointer)() const);

    virtual ~AccessorGetSet();

    virtual T get() const override;


protected:
    std::function<T ()> m_getter;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/AccessorGetSet.hpp>
