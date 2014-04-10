
#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>
#include <reflectionzeug/property_declaration.h>


namespace reflectionzeug
{

template <typename PropertyCategory, typename... MoreCategories>
class PropertyCategoryVisitor : 
    public PropertyCategoryVisitor<PropertyCategory>, 
    public PropertyCategoryVisitor<MoreCategories...>
{
};

template <typename PropertyCategory>
class PropertyCategoryVisitor<PropertyCategory> : public virtual AbstractPropertyVisitor
{
public:
    virtual void visit(PropertyCategory * property) = 0;
    
};

} // namespace reflectionzeug
