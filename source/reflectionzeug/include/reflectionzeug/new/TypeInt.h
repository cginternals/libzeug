
#pragma once


#include <reflectionzeug/new/Type.h>


namespace reflectionzeug
{


/**
*  @brief
*    Class template for defining types in the reflection system
*/
template <typename ACCESSOR>
class Type<int, ACCESSOR> : public TypeBase<int, ACCESSOR>
{
public:
    Type(const ACCESSOR & accessor);
    virtual ~Type();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypeInt.hpp>
