
#pragma once


#include <reflectionzeug/property/AbstractProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for properties that store a value
*
*  @remarks
*    Value properties are all properties that store an actual value,
*    e.g., all typed properties, and array properties (which are also
*    collections). At the moment, PropertyGroup is the only property
*    that is not a value property.
*/
class REFLECTIONZEUG_API AbstractValueProperty : public AbstractProperty
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    */
    AbstractValueProperty(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractValueProperty();
};


} // namespace reflectionzeug
