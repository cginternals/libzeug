
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>
#include <reflectionzeug/property/AbstractUnsignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for unsigned integral types
*/
template <typename T>
class PropertyUnsignedIntegral : public AbstractNumberProperty<T>, public AbstractUnsignedIntegralInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyUnsignedIntegral(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyUnsignedIntegral();

    // Virtual AbstractSignedIntegralInterface interface
    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;

    // Virtual AbstractProperty interface
    virtual void accept(AbstractVisitor * visitor) override;


protected:
    // Virtual AbstractNumberProperty interface
    virtual std::string matchRegex() const override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyUnsignedIntegral.hpp>
