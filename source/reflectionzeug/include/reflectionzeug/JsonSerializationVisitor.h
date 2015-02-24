#pragma once

#include <string>

#include <reflectionzeug/extensions/GlmProperties.hpp>
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
class JsonSerializationVisitor :
    public PropertyVisitor<
        Property<bool>,
        Property<FilePath>,
        AbstractValueProperty,
        ColorPropertyInterface,
        EnumPropertyInterface,
        UnsignedIntegralPropertyInterface,
        SignedIntegralPropertyInterface,
        FloatingPointPropertyInterface,
        StringPropertyInterface,
        Property<glm::vec3>>
{
public:
    void visit(Property<bool> * property) override;
    void visit(Property<FilePath> * property) override;
    void visit(AbstractValueProperty * property) override;
    void visit(ColorPropertyInterface * property) override;
    void visit(EnumPropertyInterface * property) override;
    void visit(UnsignedIntegralPropertyInterface * property) override;
    void visit(SignedIntegralPropertyInterface * property) override;
    void visit(FloatingPointPropertyInterface * property) override;
    void visit(StringPropertyInterface * property) override;
    void visit(Property<glm::vec3> * property) override;

    std::string propertyValue() const;

protected:
    std::string convertToJsonString(const std::string & value) const;

protected:
    std::string m_propertyValue;

};

} // namespace reflectionzeug
