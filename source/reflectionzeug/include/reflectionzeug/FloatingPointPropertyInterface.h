
#pragma once

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

class REFLECTIONZEUG_API FloatingPointPropertyInterface : public virtual AbstractValueProperty
{
public:
    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual double doubleMinimum() const = 0;
    virtual bool hasMinimum() const = 0;

    virtual double doubleMaximum() const = 0;
    virtual bool hasMaximum() const = 0;

    virtual bool hasRange() const = 0;

    virtual double doubleStep() const = 0;
    virtual bool hasStep() const = 0;

    virtual unsigned int precision() const = 0;
    virtual bool hasPrecision() const = 0;

    virtual double toDouble() const = 0;
    virtual bool fromDouble(double value) = 0;

};

} // namespace reflectionzeug
