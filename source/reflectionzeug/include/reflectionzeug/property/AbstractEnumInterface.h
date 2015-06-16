
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
    AbstractEnumInterface();
    virtual ~AbstractEnumInterface();

    virtual std::vector<std::string> strings() const = 0;

    virtual bool hasChoices() const = 0;
    virtual std::vector<std::string> choicesStrings() const = 0;
};


} // namespace reflectionzeug
