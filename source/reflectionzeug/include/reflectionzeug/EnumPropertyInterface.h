
#pragma once

#include <string>
#include <vector>

namespace reflectionzeug
{

class EnumPropertyInterface
{
public:
    virtual ~EnumPropertyInterface() = default;

    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & string) = 0;

    virtual const std::vector<std::string> & stringList() const = 0;

};

} // namespace reflectionzeug
