
#pragma once


#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AbstractStringInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for type std::string
*/
class PropertyString : public AbstractValueProperty<std::string>, public AbstractStringInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyString(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyString();

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyString.hpp>
