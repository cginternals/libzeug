
#pragma once


#include <reflectionzeug/type/AbstractPropertyValue.h>
#include <reflectionzeug/type/AbstractSignedIntegralInterface.h>


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


#include <reflectionzeug/type/PropertySignedIntegral.hpp>
