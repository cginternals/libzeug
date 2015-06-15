
#pragma once


#include <reflectionzeug/property/AbstractVisitor.h>


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
 * \see Visitor< Type >
 */
template <typename Type, typename... MoreTypes>
class Visitor : 
    public Visitor<Type>, 
    public Visitor<MoreTypes...>
{
};


/**
 * Implements a visit method for whichever type is passed as template argument.
 * The visit is done dynamically. Properties accept an AbstractVisitor and check
 * via dynamic cast if it implements a suitable visit method.
 * \see Visitor
 */
template <typename Type>
class Visitor<Type> : public virtual AbstractVisitor
{
public:
    virtual void visit(Type * typed) = 0;
};


} // namespace reflectionzeug
