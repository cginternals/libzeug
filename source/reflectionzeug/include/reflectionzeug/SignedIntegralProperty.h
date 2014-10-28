#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/SignedIntegralPropertyInterface.h>
#include <reflectionzeug/specialization_helpers.h>

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
    using Trait = isSignedIntegral<Type>;
    
public:
    template <typename... Arguments>
    SignedIntegralProperty(Arguments&&... args);
    
    virtual ~SignedIntegralProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual long long toLongLong() const;
    virtual bool fromLongLong(long long integral);

protected:
    virtual std::string matchRegex() const;
};

} // namespace reflectionzeug

#include <reflectionzeug/SignedIntegralProperty.hpp>
