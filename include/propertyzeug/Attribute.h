
#pragma once

#include <propertyzeug/propertyzeug.h>
#include "BaseAttribute.h"

namespace propertyzeug {

template <typename Type>
class Attribute;

template <>
class Attribute<int> : public BaseAttribute<int>
{
public:
    Attribute(std::string name, std::string title, int value) 
    : BaseAttribute<int>(name, title, value) {};
    
    Attribute(std::string name, std::string title, 
        std::function<int()> getter, std::function<void(int &)> setter)
    : BaseAttribute<int>(name, title, getter, setter) {};
};

} // namespace