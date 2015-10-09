
#pragma once


#include <vector>
#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for enum values
*/
class REFLECTIONZEUG_API AbstractEnumInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractEnumInterface();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractEnumInterface();

    /**
    *  @brief
    *    Get available enum values as strings
    *
    *  @return
    *    List of values
    */
    virtual std::vector<std::string> strings() const = 0;

    /**
    *  @brief
    *    Check if choices are set
    *
    *  @return
    *    'true' if choices are set, else 'false'
    */
    virtual bool hasChoices() const = 0;

    /**
    *  @brief
    *    Get available choices as strings
    *
    *  @return
    *    List of values
    */
    virtual std::vector<std::string> choicesStrings() const = 0;
};


} // namespace reflectionzeug
