
#pragma once

#include <set>
#include <string>
#include <vector>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

class ValuePropertyInterface;
class EnumPropertyInterface;

class Color;
class FilePath;

/** \brief Part of the Visitor Pattern implementation.
*/
class StandardPropertyVisitor :
    public PropertyVisitor<
        bool,
        int,
        double,
        std::string,
        Color,
        FilePath>,
    public PropertyCategoryVisitor<
        ValuePropertyInterface,
        EnumPropertyInterface>
{
};

} // namespace reflectionzeug
