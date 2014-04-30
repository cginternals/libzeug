
#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>
#include <reflectionzeug/property_declaration.h>


namespace reflectionzeug
{

/**
 * Convenience template class. Pass a list of categories as template arguments 
 * for which you want to provide visit methods.
 *
 * Usage:
 * \code{.cpp}
 * class Visitor : public PropertyCategoryVisitor<AbstractValueProperty, EnumPropertyInterface> {};
 * \endcode
 *
 * \see PropertyCategoryVisitor< PropertyCategory >
 */
template <typename PropertyCategory, typename... MoreCategories>
class PropertyCategoryVisitor : 
    public PropertyCategoryVisitor<PropertyCategory>, 
    public PropertyCategoryVisitor<MoreCategories...>
{
};

/**
 * Implements a visit method for whichever Category (e.g., EnumPropertyInterface) 
 * is passed as template argument. The visit is done dynamically. Properties accept 
 * an AbstractPropertyVisitor and check via dynamic cast if it implements a suitable visit method.
 * \see PropertyCategoryVisitor
 */
template <typename PropertyCategory>
class PropertyCategoryVisitor<PropertyCategory> : public virtual AbstractPropertyVisitor
{
public:
    virtual void visit(PropertyCategory * property) = 0;
    
};

} // namespace reflectionzeug
