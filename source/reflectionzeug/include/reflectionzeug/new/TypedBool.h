
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type bool
*/
class TypedBool : public TypedBase<bool>
{
public:
    TypedBool(Accessor<bool> * accessor);
    virtual ~TypedBool();

    void toggleValue();
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedBool.hpp>
