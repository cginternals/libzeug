
#pragma once


#include <reflectionzeug/tools/Deserializer.h>


namespace reflectionzeug {


/**
*  @brief
*    JSON deserializer
*/
class REFLECTIONZEUG_API DeserializerJSON : public Deserializer
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DeserializerJSON();

    /**
    *  @brief
    *    Constructor
    */
    virtual ~DeserializerJSON();

    // Virtual Deserializer interface
    virtual bool fromString(Variant & obj, const std::string & string) override;
};


} // namespace reflectionzeug
