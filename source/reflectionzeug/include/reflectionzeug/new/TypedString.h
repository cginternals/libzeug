
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type std::string
*/
class TypedString : public TypedBase<std::string>
{
public:
    TypedString(Accessor<std::string> * accessor);
    virtual ~TypedString();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedString.hpp>
