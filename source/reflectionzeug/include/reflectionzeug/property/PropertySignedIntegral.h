
#pragma once


#include <reflectionzeug/property/AbstractNumberProperty.h>
#include <reflectionzeug/property/AbstractSignedIntegralInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for integral types
*/
template <typename T>
class PropertySignedIntegral : public AbstractNumberProperty<T>, public AbstractSignedIntegralInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertySignedIntegral(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertySignedIntegral();

    // Virtual AbstractSignedIntegralInterface interface
    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;

    // Virtual AbstractProperty interface
    virtual void accept(AbstractVisitor * visitor) override;


protected:
    // Virtual AbstractNumberProperty interface
    virtual std::string matchRegex() const override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertySignedIntegral.hpp>
