
#pragma once


#include <string>

#include <reflectionzeug/variant/Variant.h>


namespace reflectionzeug {


/**
*  @brief
*    Variant and property deserializer
*/
class REFLECTIONZEUG_API Deserializer
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Deserializer();

    /**
    *  @brief
    *    Constructor
    */
    virtual ~Deserializer();

    /**
    *  @brief
    *    Load Variant from file
    *
    *  @param[in] obj
    *    Variant receiving the saved value
    *  @param[in] filename
    *    File name
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    bool load(Variant & obj, const std::string & filename);

    /**
    *  @brief
    *    Load Variant from string
    *
    *  @param[in] obj
    *    Variant receiving the saved value
    *  @param[in] string
    *    String representation
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    virtual bool fromString(Variant & obj, const std::string & string) = 0;
};


} // namespace reflectionzeug
