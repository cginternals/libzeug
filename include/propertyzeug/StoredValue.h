
#pragma once

#include <propertyzeug/AbstractValue.h>

namespace zeug {

/** @brief
 * Provides access to a stored value.
 */
    
template <typename Type>
class StoredValue : public AbstractValue<Type>
{
public:
    StoredValue(Type value);
    virtual ~StoredValue();

    virtual const Type & get() const;
    virtual void set(const Type & value);
protected:
    Type m_value;
};

} // namespace

#include "StoredValue.hpp"
