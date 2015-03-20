
#pragma once


#include <reflectionzeug/new/TypeBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Class template for defining types in the reflection system
*/
template <typename T, typename ACCESSOR>
class Type : public TypeBase<T, ACCESSOR>
{
public:
    Type(const ACCESSOR & accessor);
    virtual ~Type();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/Type.hpp>
