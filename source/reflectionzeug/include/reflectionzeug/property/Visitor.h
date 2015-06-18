
#pragma once


#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property visitor class
*
*    Implements a visit method for whichever type is passed as template argument.
*    The visit is done dynamically. Properties accept an AbstractVisitor and check
*    via dynamic cast if it implements a suitable visit method.
*
* @see Visitor
*/
template <typename Type>
class Visitor<Type> : public virtual AbstractVisitor
{
public:
    /**
    *  @brief
    *    Visit callback for property
    *
    *  @param[in] property
    *    Property
    */
    virtual void visit(Type * property) = 0;
};


/**
*  @brief
*    Class template to implement visitors for an arbitrary number of property types
*
*    Convenience template class: pass a list of types as template arguments 
*    for which you want to provide visit methods.
*
*    Usage:
*    \code{.cpp}
*    class Visitor : public Visitor<AbstractValueProperty, AbstractStringInterface, Property<bool>> {};
*    \endcode
*
* @see Visitor< Type >
*/
template <typename Type, typename... MoreTypes>
class Visitor : 
    public Visitor<Type>, 
    public Visitor<MoreTypes...>
{
};


} // namespace reflectionzeug
