
#pragma once


#include <reflectionzeug/property/AbstractPropertyValue.h>
#include <reflectionzeug/property/AbstractSignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T>
class PropertySignedIntegral : public AbstractPropertyValue<T>, public AbstractSignedIntegralInterface
{
public:
    template <typename... Args>
    PropertySignedIntegral(Args&&... args);

    virtual ~PropertySignedIntegral();

    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertySignedIntegral.hpp>
