
#pragma once


#include <string>

#include <stringzeug/stringzeug_api.h>


namespace stringzeug
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
STRINGZEUG_API char fromString<char>(const std::string & string);

template <>
STRINGZEUG_API unsigned char fromString<unsigned char>(const std::string & string);
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
STRINGZEUG_API std::string toString<char>(const char & value);

template <>
STRINGZEUG_API std::string toString<unsigned char>(const unsigned char & value);
//@}


} // namespace stringzeug


#include <stringzeug/conversion.hpp>
