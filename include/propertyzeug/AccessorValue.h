
#pragma once

#include <functional>
#include "AbstractValue.h"

namespace propertyzeug {

// TODO Implement method pointer option
    
template <typename Type>
class PROPERTYZEUG_API AccessorValue : public AbstractValue<Type>
{
public:
    AccessorValue(std::function<const Type & ()> getter,
                  std::function<void(const Type &)> setter);
    
    template <class Object>
    AccessorValue(Object & object,
                  const Type & (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(const Type &));
    
    template <class Object>
    AccessorValue(Object & object,
                  Type (Object::*getter_pointer)() const,
                  void (Object::*setter_pointer)(Type));

    
    virtual ~AccessorValue();

    virtual const Type & get() const;
    virtual void set(const Type & value);
protected:
    std::function<const Type & ()> m_getter;
    std::function<void(const Type &)> m_setter;
};

template <typename Type>
AccessorValue<Type>::AccessorValue(std::function<const Type & ()> getter,
    std::function<void(const Type &)> setter)
:   m_getter(getter)
,   m_setter(setter)
{   
}
    
template <typename Type>
template <class Object>
AccessorValue<Type>::AccessorValue(Object & object,
    const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
{
    m_getter = [&object, getter_pointer] () -> const Type & {
        return (object.*getter_pointer)();
    };
    
    m_setter = [&object, setter_pointer] (const Type & value) {
        (object.*setter_pointer)(value);
    };
}
    
template <typename Type>
template <class Object>
AccessorValue<Type>::AccessorValue(Object & object,
    Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
{
    m_getter = [&object, getter_pointer] () -> const Type & {
        return (object.*getter_pointer)();
    };
    
    m_setter = [&object, setter_pointer] (const Type & value) {
        (object.*setter_pointer)(value);
    };
}
    

template <typename Type>
AccessorValue<Type>::~AccessorValue()
{
}

template <typename Type>
const Type & AccessorValue<Type>::get() const
{
    return m_getter();
}

template <typename Type>
void AccessorValue<Type>::set(const Type & value)
{
    m_setter(value);
}

} // namespace