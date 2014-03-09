
#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/ValuePropertyInterface.h>

namespace reflectionzeug
{

class EnumPropertyInterface : public virtual ValuePropertyInterface
{
public:
    virtual const std::vector<std::string> & stringList() const = 0;

};

} // namespace reflectionzeug
