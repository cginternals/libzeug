#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{

template <typename PropertyType, typename... MorePropertyTypes>
class PropertyVisitor;

/**
 * \brief The base class of all property visitors.
 *
 * Usually specific visitors don't inherit from it.
 * \see PropertyVisitor
 * \see PropertyCategoryVisitor
 */
class REFLECTIONZEUG_API AbstractPropertyVisitor
{
public:
    virtual ~AbstractPropertyVisitor() = 0;

    template <typename PropertyType>
    PropertyVisitor<PropertyType> * asVisitor();

    template <typename PropertyType>
    PropertyVisitor<PropertyType> * asVisitor() const;
};

} // namespace reflectionzeug

#include <reflectionzeug/AbstractPropertyVisitor.hpp>
