
#pragma once


#include <reflectionzeug/type/AbstractPropertyArray.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for array types
*/
template <typename T, size_t Size>
class PropertyArray : public AbstractPropertyArray<T, Size>
{
public:
    template <typename... Args>
    PropertyArray(Args&&... args);

    virtual ~PropertyArray();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/PropertyArray.hpp>
