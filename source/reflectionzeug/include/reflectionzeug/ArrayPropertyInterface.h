
#pragma once

#include <functional>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValuePropertyInterface.h>

namespace reflectionzeug
{

class REFLECTIONZEUG_API ArrayPropertyInterface : public ValuePropertyInterface
{
public:
    ArrayPropertyInterface(const std::string & name);

    virtual bool isArray() const;
    
};

} // namespace reflectionzeug
