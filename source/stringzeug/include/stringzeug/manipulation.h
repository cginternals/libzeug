
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
STRINGZEUG_API std::vector<std::string> parseArray(const std::string & string, size_t size);

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
STRINGZEUG_API std::vector<std::string> split(const std::string & string, char delimiter);

/**
*  @brief
*    Check if a string contains a substring
*
*  @param[in] string
*    Input string
*  @param[in] containsstring
*    String that is checked if contained in first param string
*
*  @return
*    true if string contains containsstring, false otherwise
*/
STRINGZEUG_API bool contains(const std::string & string, const std::string & containsstring);

/**
*  @brief
*    Check if a string starts with a given prefix
*
*  @param[in] string
*    Input string
*  @param[in] prefix
*    Prefix to be checked
*
*  @return
*    true if string starts with prefix, false otherwise
*/
STRINGZEUG_API bool hasPrefix(const std::string & string, const std::string & prefix);

/**
*  @brief
*    Check if a string ends with a given suffix
*
*  @param[in] string
*    Input string
*  @param[in] suffix
*    Suffix to be checked
*
*  @return
*    true if string ends with suffix, false otherwise
*/
STRINGZEUG_API bool hasSuffix(const std::string & string, const std::string & suffix);


} // namespace stringzeug


#include <stringzeug/manipulation.hpp>
