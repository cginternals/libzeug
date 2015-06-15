
#pragma once


#include <reflectionzeug/type/AbstractPropertyValue.h>
#include <reflectionzeug/type/AbstractUnsignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for unsigned integral types
*/
template <typename T>
class PropertyUnsignedIntegral : public AbstractPropertyValue<T>, public AbstractUnsignedIntegralInterface
{
public:
    template <typename... Args>
    PropertyUnsignedIntegral(Args&&... args);

    virtual ~PropertyUnsignedIntegral();

    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/PropertyUnsignedIntegral.hpp>
