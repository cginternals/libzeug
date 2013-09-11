
#pragma once

#include "propertyzeug/propertyzeug.h"

namespace propertyzeug {
    
/** @brief
 * The base class for value implementations of ValueProperty.
 */

template <typename Type>
class PROPERTYZEUG_API AbstractValue
{
public:
    virtual ~AbstractValue() {};
    
    virtual const Type & get() const = 0;
    virtual void set(const Type & value) = 0;
};

} // namespace
