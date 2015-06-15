
#pragma once


#include <reflectionzeug/type/AbstractPropertyValue.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for class types
*/
template <typename T>
class PropertyClass : public AbstractPropertyValue<T>
{
public:
    template <typename... Args>
    PropertyClass(Args&&... args);

    virtual ~PropertyClass();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/type/PropertyClass.hpp>
