
#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/SignedIntegralPropertyInterface.h>


namespace reflectionzeug
{

/**
 * \brief Provides the property implementation for signed integral types.
 *
 * Extends the NumberProperty by implementing necessary methods for uniform access
 * of all signed integral types.
 *
 * \ingroup property_hierarchy
 */
template <typename Type>
class SignedIntegralProperty : public SignedIntegralPropertyInterface, public NumberProperty<Type>
{
public:
    template <typename... Arguments>
    SignedIntegralProperty(Arguments&&... args);
    
    virtual ~SignedIntegralProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual long long uLongLongMinimum();
    virtual bool hasMinimum() const;

    virtual long long uLongLongMaximum();
    virtual bool hasMaximum() const;

    virtual bool hasRange() const;

    virtual long long uLongLongStep();
    virtual bool hasStep() const;

    virtual long long toULongLong() const;
    virtual bool fromULongLong(long long integral);

protected:
    virtual std::string matchRegex() const;

};

} // namespace reflectionzeug

#include "SignedIntegralProperty.hpp"
