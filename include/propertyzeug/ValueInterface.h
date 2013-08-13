
#pragma once

#include "propertyzeug/propertyzeug.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API ValueInterface
{
public:
    virtual const Type & get() const = 0;
    virtual void set(const Type & value) = 0;
};

} // namespace