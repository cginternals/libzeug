
#pragma once


#include <reflectionzeug/property/AbstractTypedProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for numeric property types
*
*    Two option are set in the constructor:
*    - minimum (Type): initialized to the lowest possible value of Type
*    - maximum (Type): initialized to the greatest possible value of Type
*/
template <typename Type>
class AbstractNumberProperty : public AbstractTypedProperty<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    AbstractNumberProperty(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractNumberProperty() = 0;

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;


protected:
    /**
    *  @brief
    *    Get regular expression to check against input strings
    *
    *  @return
    *    Regular expression
    */
    virtual std::string matchRegex() const = 0;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractNumberProperty.hpp>
