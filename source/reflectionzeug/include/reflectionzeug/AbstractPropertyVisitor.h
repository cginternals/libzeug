
#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{

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

};

} // namespace reflectionzeug
