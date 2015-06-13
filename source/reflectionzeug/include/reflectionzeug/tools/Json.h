
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class Variant;


/**
*  @brief
*    JSON tools
*/
class REFLECTIONZEUG_API Json
{
public:
    /**
    *  @brief
    *    Save variant in JSON format
    *
    *  @param[in] value
    *    Variant value
    *
    *  @return
    *    JSON representation
    */
    static std::string stringify(const Variant & value);
};


} // namespace reflectionzeug
