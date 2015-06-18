
#pragma once


#include <string>
#include <vector>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Utility methods which deal with common string conversion, string manipulation and regular expressions
*/
namespace util
{


//@{
/**
*  @brief
*    Convert from std::string to Type
*
*  @param[in] string
*    String representation
*
*  @return
*    Primitive type value
*/
template <typename Type>
Type fromString(const std::string & string);

template <>
REFLECTIONZEUG_API char fromString<char>(const std::string & string);

template <>
REFLECTIONZEUG_API unsigned char fromString<unsigned char>(const std::string & string);
//@}

//@{
/**
*  @brief
*    Convert from Type to std::string
*
*  @param[in] value
*    Primitive type value
*
*  @return
*    String representation
*/
template <typename Type>
std::string toString(const Type & value);

template <>
REFLECTIONZEUG_API std::string toString<char>(const char & value);

template <>
REFLECTIONZEUG_API std::string toString<unsigned char>(const unsigned char & value);
//@}

//@{
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
std::string join(const Iterable & iterable, const std::string & separator);

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
REFLECTIONZEUG_API std::string trim(const std::string & string, bool removeAllWhitespace = false);

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
REFLECTIONZEUG_API std::vector<std::string> splitArray(const std::string & string, size_t size);
    
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
REFLECTIONZEUG_API std::vector<std::string> split(const std::string & input, char delimiter);

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
REFLECTIONZEUG_API bool matchesRegex(const std::string & string, const std::string & regex);

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
REFLECTIONZEUG_API std::vector<std::string> extract(const std::string & string, const std::string & regex);
//@}


} // namespace util


} // namespace reflectionzeug


#include <reflectionzeug/base/util.hpp>
