
#pragma once

#include <functional>
#include "ValueInterface.h"

namespace propertyzeug {

// TODO Implement method pointer option
    
template <typename Type>
class PROPERTYZEUG_API AccessorValue : public ValueInterface<Type>
{
public:
    AccessorValue(std::function<const Type & ()> getter, std::function<void(const Type &)> setter);
    virtual ~AccessorValue();

    virtual const Type & get() const;
    virtual void set(const Type & value);
protected:
    std::function<const Type & ()> m_getter;
    std::function<void(const Type &)> m_setter;
};

template <typename Type>
AccessorValue<Type>::AccessorValue(std::function<const Type & ()> getter, std::function<void(const Type &)> setter)
:   m_getter(getter)
,   m_setter(setter)
{   
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