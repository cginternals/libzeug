
#pragma once


#include <reflectionzeug/property/AbstractValueProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for class types
*/
template <typename T>
class PropertyClass : public AbstractValueProperty<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyClass(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyClass();

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyClass.hpp>
