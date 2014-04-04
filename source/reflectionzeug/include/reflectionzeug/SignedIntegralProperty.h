
#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/SignedIntegralPropertyInterface.h>


namespace reflectionzeug
{

template <typename Type>
class SignedIntegralProperty : public SignedIntegralPropertyInterface, public NumberProperty<Type>
{
public:
    template <typename... Arguments>
    SignedIntegralProperty(Arguments&&... args);

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);

    virtual long long uLongLongMinimum();
    virtual bool hasMinimum() const;

    virtual long long uLongLongMaximum();
    virtual bool hasMaximum() const;

    virtual bool hasRange() const;

    virtual long long uLongLongStep();
    virtual bool hasStep() const;

    virtual long long toULongLong() const;
    virtual bool fromULongLong(long long integral);

};

} // namespace reflectionzeug

#include "SignedIntegralProperty.hpp"
