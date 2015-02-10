#include <reflectionzeug/JsonSerializationVisitor.h>

#include <reflectionzeug/Property.h>

namespace reflectionzeug
{

void JsonSerializationVisitor::visit(Property<bool> *property)
{
    m_propertyValue = property->value() ? "true" : "false";
}

void JsonSerializationVisitor::visit(Property<FilePath> *property)
{
    m_propertyValue = convertToJsonString(property->value().string());
}

void JsonSerializationVisitor::visit(AbstractValueProperty *property)
{
    m_propertyValue = "";
}

void JsonSerializationVisitor::visit(ColorPropertyInterface *property)
{
    m_propertyValue = convertToJsonString(property->toColor().toString());
}

void JsonSerializationVisitor::visit(EnumPropertyInterface *property)
{
    m_propertyValue = convertToJsonString(property->toString());
}

void JsonSerializationVisitor::visit(UnsignedIntegralPropertyInterface *property)
{
    m_propertyValue = util::toString(property->toULongLong());
}

void JsonSerializationVisitor::visit(SignedIntegralPropertyInterface *property)
{
    m_propertyValue = util::toString(property->toLongLong());
}

void JsonSerializationVisitor::visit(FloatingPointPropertyInterface *property)
{
    m_propertyValue = util::toString(property->toDouble());
}

void JsonSerializationVisitor::visit(StringPropertyInterface *property)
{
    m_propertyValue = convertToJsonString(property->toString());
}

void JsonSerializationVisitor::visit(Property<glm::vec3> *property)
{
    std::stringstream stream;
    stream << "(" << property->value().x << ", " << property->value().y << ", " << property->value().z << ")";
    m_propertyValue = convertToJsonString(stream.str());
}

std::string JsonSerializationVisitor::propertyValue() const
{
    return m_propertyValue;
}

std::string JsonSerializationVisitor::convertToJsonString(const std::string & value) const
{
    std::stringstream stream;
    stream << "\"" << value << "\"";
    return stream.str();
}

} // namespace reflectionzeug
