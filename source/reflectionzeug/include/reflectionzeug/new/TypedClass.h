
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for class types
*/
template <typename T, typename Accessor>
class TypedClass : public TypedBase<T, Accessor>
{
public:
    TypedClass(const Accessor & accessor);
    virtual ~TypedClass();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedClass.hpp>
