
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type std::string
*/
template <typename Accessor>
class TypedString : public TypedBase<std::string, Accessor>
{
public:
    TypedString(const Accessor & accessor);
    virtual ~TypedString();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedString.hpp>
