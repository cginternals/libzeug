
#pragma once


#include <reflectionzeug/property/AbstractPropertyValue.h>
#include <reflectionzeug/property/AbstractStringInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type std::string
*/
class PropertyString : public AbstractPropertyValue<std::string>, public AbstractStringInterface
{
public:
    template <typename... Args>
    PropertyString(Args&&... args);

    virtual ~PropertyString();

    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyString.hpp>
