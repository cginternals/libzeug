
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type std::string
*/
class TypedString : public AbstractTyped<std::string>
{
public:
    template <typename... Args>
    TypedString(Args&&... args);

    virtual ~TypedString();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedString.hpp>
