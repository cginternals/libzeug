
#pragma once


#include <string>
#include <vector>

#include <stringzeug/stringzeug_api.h>


namespace stringzeug
{


/**
*  @brief
*    Join all values of a container in a single string
*
*  @param[in] iterable
*    Container
*  @param[in] separator
*    String separator
*
*  @return
*    String
*/
template <class Iterable>
STRINGZEUG_API std::string join(const Iterable & iterable, const std::string & separator);

/**
*  @brief
*    Trim string by removing whitespace
*
*  @param[in] string
*    String
*  @param[in] removeAllWhitespace
*    'true': remove whitespace everywhere in the string, 'false': remove whitespace at the beginning and the end of the string
*
*  @return
*    String
*/
STRINGZEUG_API std::string trim(const std::string & string, bool removeAllWhitespace = false);

/**
*  @brief
*    Split string into substrings
*
*  @param[in] size
*    Number of elements
*  @param[in] string
*    Input string of the form "(<value>,<value>,<value>...)"
*
*  @return
*    List of strings
*/
STRINGZEUG_API std::vector<std::string> splitArray(const std::string & string, size_t size);

/**
*  @brief
*    Split string into substrings
*
*  @param[in] string
*    Input string
*  @param[in] delimiter
*    Character that marks the next element
*
*  @return
*    List of strings
*/
STRINGZEUG_API std::vector<std::string> split(const std::string & input, char delimiter);


} // namespace stringzeug


#include <stringzeug/manipulation.hpp>
