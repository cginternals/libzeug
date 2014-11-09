#pragma once

#include <set>
#include <vector>

#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/PropertyVisitor.h>

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
        Property<bool>,
        Property<FilePath>,
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
