
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

template <typename Type>
class Property;

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
        FilePath,
        std::vector<bool>,
        std::vector<int>,
        std::vector<double>>,
    public PropertyCategoryVisitor<
        ValuePropertyInterface,
        EnumPropertyInterface>
{

};

} // namespace reflectionzeug
