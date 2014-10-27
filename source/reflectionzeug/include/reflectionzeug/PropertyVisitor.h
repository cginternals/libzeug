#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>
#include <reflectionzeug/property_declaration.h>

namespace reflectionzeug
{

/**
 * Convenience template class. Pass a list of types as template arguments 
 * for which you want to provide visit methods.
 *
 * Usage:
 * \code{.cpp}
 * class Visitor : public PropertyVisitor<AbstractValueProperty, StringPropertyInterface, Property<bool>> {};
 * \endcode
 *
 * \see PropertyVisitor< PropertyType >
 */
template <typename PropertyType, typename... MorePropertyTypes>
class PropertyVisitor : 
    public PropertyVisitor<PropertyType>, 
    public PropertyVisitor<MorePropertyTypes...>
{
};

/**
 * Implements a visit method for whichever type is passed as template argument.
 * The visit is done dynamically. Properties accept an AbstractPropertyVisitor and check
 * via dynamic cast if it implements a suitable visit method.
 * \see PropertyVisitor
 */
template <typename PropertyType>
class PropertyVisitor<PropertyType> : public virtual AbstractPropertyVisitor
{
public:
    virtual void visit(PropertyType * property) = 0;
};

} // namespace reflectionzeug





