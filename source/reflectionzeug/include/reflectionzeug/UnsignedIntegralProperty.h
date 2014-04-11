
#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>


namespace reflectionzeug
{

template <typename Type>
class UnsignedIntegralProperty : public UnsignedIntegralPropertyInterface, public NumberProperty<Type>
{
public:
    template <typename... Arguments>
    UnsignedIntegralProperty(Arguments&&... args);

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);

    virtual unsigned long long uLongLongMinimum();
    virtual bool hasMinimum() const;

    virtual unsigned long long uLongLongMaximum();
    virtual bool hasMaximum() const;

    virtual bool hasRange() const;

    virtual unsigned long long uLongLongStep();
    virtual bool hasStep() const;

    virtual unsigned long long toULongLong() const;
    virtual bool fromULongLong(unsigned long long integral);

protected:
    virtual std::string matchRegex() const;

};

} // namespace reflectionzeug

#include "UnsignedIntegralProperty.hpp"
