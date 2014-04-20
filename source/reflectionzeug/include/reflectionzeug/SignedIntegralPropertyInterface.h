
#pragma once

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

class REFLECTIONZEUG_API SignedIntegralPropertyInterface : public virtual AbstractValueProperty
{
public:    
    virtual void accept(AbstractPropertyVisitor * visitor);
    
    virtual long long uLongLongMinimum() = 0;
    virtual bool hasMinimum() const = 0;

    virtual long long uLongLongMaximum() = 0;
    virtual bool hasMaximum() const = 0;

    virtual bool hasRange() const = 0;

    virtual long long uLongLongStep() = 0;
    virtual bool hasStep() const = 0;

    virtual long long toULongLong() const = 0;
    virtual bool fromULongLong(long long integral) = 0;

};

} // namespace reflectionzeug
