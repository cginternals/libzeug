
#pragma once

#include <set>
#include <vector>

#include <reflectionzeug/PropertyVisitor.h>
#include <reflectionzeug/PropertyCategoryVisitor.h>

namespace reflectionzeug
{

class AbstractValueProperty;
class ColorPropertyInterface;
class EnumPropertyInterface;
class UnsignedIntegralPropertyInterface;
class SignedIntegralPropertyInterface;
class FloatingPointPropertyInterface;
class StringPropertyInterface;

class Color;
class FilePath;

/** \brief Part of the Visitor Pattern implementation.
*/
class StandardPropertyVisitor :
    public PropertyVisitor<
        bool,
        FilePath>,
    public PropertyCategoryVisitor<
        AbstractValueProperty,
        ColorPropertyInterface,
        EnumPropertyInterface,
        UnsignedIntegralPropertyInterface,
        SignedIntegralPropertyInterface,
        FloatingPointPropertyInterface,
        StringPropertyInterface>
{
};

} // namespace reflectionzeug
