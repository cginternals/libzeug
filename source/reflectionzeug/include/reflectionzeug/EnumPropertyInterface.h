
#pragma once

#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/ValuePropertyInterface.h>

namespace reflectionzeug
{

class REFLECTIONZEUG_API EnumPropertyInterface : public virtual ValuePropertyInterface
{
public:
    virtual ~EnumPropertyInterface() = 0;
    
    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);
    
    virtual bool hasChoices() const = 0;

    virtual std::vector<std::string> stringChoices() const = 0;
    virtual std::vector<std::string> strings() const = 0;

};

} // namespace reflectionzeug
