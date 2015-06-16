
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>
#include <reflectionzeug/property/AbstractSignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for signed integral types
*/
template <typename T>
class PropertySignedIntegral : public AbstractNumberProperty<T>, public AbstractSignedIntegralInterface
{
public:
    template <typename... Args>
    PropertySignedIntegral(Args&&... args);

    virtual ~PropertySignedIntegral();

    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;

    virtual void accept(AbstractVisitor * visitor) override;


protected:
    virtual std::string matchRegex() const;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertySignedIntegral.hpp>
