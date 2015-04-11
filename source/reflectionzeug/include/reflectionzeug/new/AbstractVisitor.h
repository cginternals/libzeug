
#pragma once


#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


template <typename PropertyType, typename... MorePropertyTypes>
class Visitor;


/**
 * \brief The base class of all property visitors.
 *
 * Usually specific visitors don't inherit from it.
 * \see PropertyVisitor
 * \see PropertyCategoryVisitor
 */
class REFLECTIONZEUG_API AbstractVisitor
{
public:
    AbstractVisitor();
    virtual ~AbstractVisitor();

    template <typename Type>
    Visitor<Type> * asVisitor();

    template <typename Type>
    Visitor<Type> * asVisitor() const;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/AbstractVisitor.hpp>