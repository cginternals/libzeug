#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/UnsignedIntegralPropertyInterface.h>

namespace reflectionzeug
{

/**
 * \brief Provides the property implementation for unsigned integral types.
 *
 * Extends the NumberProperty by implementing necessary methods for uniform access
 * of all unsigned integral types.
 *
 * \ingroup property_hierarchy
 */
template <typename Type>
class UnsignedIntegralProperty : public NumberProperty<Type, UnsignedIntegralPropertyInterface>
{
public:
    virtual ~UnsignedIntegralProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual unsigned long long toULongLong() const;
    virtual bool fromULongLong(unsigned long long integral);

protected:
    virtual std::string matchRegex() const;
};

} // namespace reflectionzeug

#include <reflectionzeug/UnsignedIntegralProperty.hpp>
