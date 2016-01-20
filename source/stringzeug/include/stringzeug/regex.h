
#pragma once


#include <string>
#include <vector>

#include <stringzeug/stringzeug_api.h>


namespace stringzeug
{


/**
*  @brief
*    Check if a regex matches a given string
*
*  @param[in] string
*    Input string
*  @param[in] regex
*    Regular expression
*
*  @return
*    'true' if regex matches the string, else 'false'
*/
STRINGZEUG_API bool matchesRegex(const std::string & string, const std::string & regex);

/**
*  @brief
*    Extract substrings matched by a regex
*
*  @param[in] string
*    Input string
*  @param[in] regex
*    Regular expression
*
*  @return
*    List of results that match the regex
*/
STRINGZEUG_API std::vector<std::string> extract(const std::string & string, const std::string & regex);


} // namespace stringzeug
