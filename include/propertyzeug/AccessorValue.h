
#pragma once

#include <functional>
#include "ValueInterface.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API AccessorValue : public ValueInterface<Type>
{
public:
    AccessorValue(std::function<Type()> getter, std::function<void(Type &)> setter);
    virtual ~AccessorValue();

    virtual Type get() const;
    virtual void set(Type value);
private:
    std::function<Type()> m_getter;
    std::function<void(Type &)> m_setter;
};

template <typename Type>
AccessorValue<Type>::AccessorValue(std::function<Type()> getter, std::function<void(Type &)> setter)
:   m_getter(getter)
,   m_setter(setter)
{   
}

template <typename Type>
AccessorValue<Type>::~AccessorValue()
{
}

template <typename Type>
Type AccessorValue<Type>::get() const
{
    return m_getter();
}

template <typename Type>
void AccessorValue<Type>::set(Type value)
{
    m_setter(value);
}

} // namespace