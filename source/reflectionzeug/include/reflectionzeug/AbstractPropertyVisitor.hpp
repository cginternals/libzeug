#pragma once

#include <reflectionzeug/AbstractPropertyVisitor.h>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename PropertyType>
PropertyVisitor<PropertyType> * AbstractPropertyVisitor::asVisitor()
{
    return dynamic_cast<PropertyVisitor<PropertyType> *>(this);
}

template <typename PropertyType>
PropertyVisitor<PropertyType> * AbstractPropertyVisitor::asVisitor() const
{
    return dynamic_cast<PropertyVisitor<PropertyType> *>(this);
}

} // namespace reflectionzeug
