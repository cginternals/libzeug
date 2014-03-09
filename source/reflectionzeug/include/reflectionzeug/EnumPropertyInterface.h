
#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

class EnumPropertyInterface : public virtual ValueProperty
{
public:
    virtual const std::vector<std::string> & stringList() const = 0;

};

} // namespace reflectionzeug
