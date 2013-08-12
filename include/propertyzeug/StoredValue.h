
#pragma once

#include "ValueInterface.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API StoredValue : public ValueInterface<Type>
{
public:
    StoredValue(Type value);
    virtual ~StoredValue();

    virtual Type get() const;
    virtual void set(Type value);
protected:
    Type m_value;
};

template <typename Type>
StoredValue<Type>::StoredValue(Type value)
:   m_value(value)
{   
}

template <typename Type>
StoredValue<Type>::~StoredValue()
{
}

template <typename Type>
Type StoredValue<Type>::get() const
{
    return m_value;
}

template <typename Type>
void StoredValue<Type>::set(Type value)
{
    m_value = value;
}

} // namespace