
#pragma once


#include <reflectionzeug/property/AbstractArrayProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for array types
*/
template <typename T, size_t Size>
class PropertyArray : public AbstractArrayProperty<T, Size>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyArray(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyArray();

    // Virtual AbstractProperty interface
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyArray.hpp>
