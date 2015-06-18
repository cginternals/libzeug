
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for boolean values
*/
class REFLECTIONZEUG_API AbstractBooleanInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractBooleanInterface();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractBooleanInterface();

    /**
    *  @brief
    *    Convert value to boolean
    *
    *  @return
    *    Boolean value
    */
    virtual bool toBool() const = 0;

    /**
    *  @brief
    *    Convert value from boolean
    *
    *  @param[in] value
    *    Boolean value
    *
    *  @return
    *    'true' if the value could be set, else 'false'
    */
    virtual bool fromBool(bool value) = 0;
};


} // namespace reflectionzeug
