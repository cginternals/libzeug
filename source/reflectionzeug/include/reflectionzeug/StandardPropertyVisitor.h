
#pragma once

#include <set>
#include <string>
#include <vector>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

class AbstractValueProperty;
class EnumPropertyInterface;
class UnsignedIntegralPropertyInterface;
class SignedIntegralPropertyInterface;
class FloatingPointPropertyInterface;


class Color;
class FilePath;

/** \brief Part of the Visitor Pattern implementation.
*/
class StandardPropertyVisitor :
    public PropertyVisitor<
        bool,
        std::string,
        Color,
        FilePath>,
    public PropertyCategoryVisitor<
        AbstractValueProperty,
        EnumPropertyInterface,
        UnsignedIntegralPropertyInterface,
        SignedIntegralPropertyInterface,
        FloatingPointPropertyInterface>
{
};

} // namespace reflectionzeug
