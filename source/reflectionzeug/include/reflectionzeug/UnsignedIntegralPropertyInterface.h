
#pragma once

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

class REFLECTIONZEUG_API UnsignedIntegralPropertyInterface : public virtual AbstractValueProperty
{
public:
    virtual ~UnsignedIntegralPropertyInterface() = 0;
    
    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);
    
    virtual unsigned long long uLongLongMinimum() = 0;
    virtual bool hasMinimum() const = 0;

    virtual unsigned long long uLongLongMaximum() = 0;
    virtual bool hasMaximum() const = 0;

    virtual bool hasRange() const = 0;

    virtual unsigned long long uLongLongStep() = 0;
    virtual bool hasStep() const = 0;

    virtual unsigned long long toULongLong() const = 0;
    virtual bool fromULongLong(unsigned long long integral) = 0;

};

} // namespace reflectionzeug
