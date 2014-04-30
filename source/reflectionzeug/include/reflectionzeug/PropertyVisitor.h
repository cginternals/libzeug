
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
 * class Visitor : public PropertyVisitor<int, float, bool, std::string> {};
 * \endcode
 *
 * \see PropertyVisitor< Type >
 */
template <typename Type, typename... MoreTypes>
class PropertyVisitor : public PropertyVisitor<Type>, public PropertyVisitor<MoreTypes...>
{
};

/**
 * Implements a visit method for whichever type is passed as template argument.
 * The visit is done dynamically. Properties accept an AbstractPropertyVisitor and check
 * via dynamic cast if it implements a suitable visit method.
 * \see PropertyVisitor
 */
template <typename Type>
class PropertyVisitor<Type> : public virtual AbstractPropertyVisitor
{
public:
    virtual void visit(Property<Type> * property) = 0;
    
};

} // namespace reflectionzeug





