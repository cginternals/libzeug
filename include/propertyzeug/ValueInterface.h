
#pragma once

#include "propertyzeug/propertyzeug.h"

namespace propertyzeug {

template <typename Type>
class PROPERTYZEUG_API ValueInterface
{
public:
    virtual Type get() const = 0;
    virtual void set(Type value) = 0;
};

} // namespace