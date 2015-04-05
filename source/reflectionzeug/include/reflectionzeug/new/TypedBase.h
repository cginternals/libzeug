
#pragma once


#include <memory>

#include <reflectionzeug/new/Accessor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Base class for typed values, defining data type and accessor to value
*/
template <typename Type>
class TypedBase
{
public:
    TypedBase(Accessor<Type> * accessor);
    virtual ~TypedBase();

    Type get() const;
    void set(const Type & value);


protected:
    std::unique_ptr<Accessor<Type>> m_accessor;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedBase.hpp>
