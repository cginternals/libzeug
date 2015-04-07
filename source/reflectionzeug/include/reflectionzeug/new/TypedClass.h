
#pragma once


#include <reflectionzeug/new/AbstractTyped.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for class types
*/
template <typename T>
class TypedClass : public AbstractTyped<T>
{
public:
    template <typename... Args>
    TypedClass(Args&&... args);

    virtual ~TypedClass();

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedClass.hpp>
