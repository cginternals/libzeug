
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>
#include <reflectionzeug/property/AbstractUnsignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for unsigned integral types
*/
template <typename T>
class PropertyUnsignedIntegral : public AbstractNumberProperty<T>, public AbstractUnsignedIntegralInterface
{
public:
    template <typename... Args>
    PropertyUnsignedIntegral(Args&&... args);

    virtual ~PropertyUnsignedIntegral();

    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;

    virtual void accept(AbstractVisitor * visitor) override;


protected:
    virtual std::string matchRegex() const;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyUnsignedIntegral.hpp>
