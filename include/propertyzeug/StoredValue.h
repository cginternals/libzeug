
#pragma once

#include "AbstractValue.h"

namespace propertyzeug {

/** @brief
 * Provides access to a stored value.
 */
    
template <typename Type>
class PROPERTYZEUG_API StoredValue : public AbstractValue<Type>
{
public:
    StoredValue(Type value);
    virtual ~StoredValue();

    virtual const Type & get() const;
    virtual void set(const Type & value);
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
const Type &  StoredValue<Type>::get() const
{
    return m_value;
}

template <typename Type>
void StoredValue<Type>::set(const Type & value)
{
    m_value = value;
}

} // namespace