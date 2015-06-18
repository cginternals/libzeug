
#pragma once


#include <string>

#include <reflectionzeug/variant/Variant.h>


namespace reflectionzeug {


/**
*  @brief
*    JSON tools
*/
class REFLECTIONZEUG_API JSON
{
public:
    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[in] obj
    *    Variant receiving the JSON representation
    *  @param[in] json
    *    JSON document
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    static bool parse(Variant & obj, const std::string & json);

    /**
    *  @brief
    *    Convert value to JSON notation
    *
    *  @param[in] obj
    *    Variant (object or array)
    *  @param[in] nice
    *    Produce nice readable output?
    *  @param[in] indent
    *    Indendation string, used on the start of every new line
    *
    *  @return
    *    JSON representation
    *
    *  @remarks
    *    Only object or arrays can be converted into JSON, for every other type, "" is returned.
    */
    static std::string stringify(const Variant & obj, bool nice = false, const std::string & indent = "");

    /**
    *  @brief
    *    Load JSON from file
    *
    *  @param[in] obj
    *    Variant receiving the JSON representation
    *  @param[in] filename
    *    File name
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    static bool load(Variant & obj, const std::string & filename);

    /**
    *  @brief
    *    Save JSON to file
    *
    *  @param[in] obj
    *    Variant (object or array)
    *  @param[in] filename
    *    File name
    *  @param[in] nice
    *    Produce nice readable output?
    */
    static void save(const Variant & obj, const std::string & filename, bool nice = false);


};


} // namespace reflectionzeug
