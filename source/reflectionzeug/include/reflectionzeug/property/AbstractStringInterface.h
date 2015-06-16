
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    Interface for typed values to be accessed via strings
*
*  @remarks
*    Since toString/fromString exist in every value property,
*    this interface is empty. It is still important and can be
*    used to indicate that a property type shall be treated as
*    a string value.
*/
class REFLECTIONZEUG_API AbstractStringInterface
{
public:
    AbstractStringInterface();
    virtual ~AbstractStringInterface();
};


} // namespace reflectionzeug
