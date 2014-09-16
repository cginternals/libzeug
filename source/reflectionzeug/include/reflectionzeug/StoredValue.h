
#pragma once

#include <reflectionzeug/AbstractValue.h>

namespace reflectionzeug
{

/**
 * Provides access to a stored value.
 */  
template <typename Type>
class StoredValue : public AbstractValue<Type>
{
public:
    StoredValue(const Type & value);
    virtual ~StoredValue();

    virtual Type get() const;
    virtual void set(const Type & value);

protected:
    Type m_value;
};

} // namespace reflectionzeug

#include <reflectionzeug/StoredValue.hpp>
