
#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>
#include <reflectionzeug/property_declaration.h>

namespace reflectionzeug
{

template <typename Type, typename... MoreTypes>
class PropertyVisitor : public PropertyVisitor<Type>, public PropertyVisitor<MoreTypes...>
{
};

template <typename Type>
class PropertyVisitor<Type> : public virtual AbstractPropertyVisitor
{
public:
    virtual void visit(Property<Type> * property) = 0;
    
};

} // namespace reflectionzeug





