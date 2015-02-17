#include <reflectionzeug/SetValuePropertyVisitor.h>

#include <reflectionzeug/Property.h>

namespace reflectionzeug
{

SetValuePropertyVisitor::SetValuePropertyVisitor(const Variant & variant)
    : m_variant(variant)
{

}

void SetValuePropertyVisitor::visit(Property<bool> *property)
{
    if (m_variant.hasType<bool>())
    {
        property->setValue(m_variant.value<bool>());
    }
}

void SetValuePropertyVisitor::visit(Property<FilePath> *property)
{
    if (m_variant.hasType<std::string>())
    {
        assert(property->fromString(m_variant.value<std::string>()));
    }
}

void SetValuePropertyVisitor::visit(AbstractValueProperty *property)
{

}

void SetValuePropertyVisitor::visit(ColorPropertyInterface *property)
{
    if (m_variant.hasType<std::string>())
    {
        // ignore invalid colors
        if (m_variant.value<std::string>().compare("#00") != 0)
        {
            assert(property->fromString(m_variant.value<std::string>()));
        }
    }
}

void SetValuePropertyVisitor::visit(EnumPropertyInterface *property)
{
    if (m_variant.hasType<std::string>())
    {
        assert(property->fromString(m_variant.value<std::string>()));
    }
}

void SetValuePropertyVisitor::visit(UnsignedIntegralPropertyInterface *property)
{
    if (m_variant.hasType<unsigned long long>())
    {
        assert(property->fromULongLong(m_variant.value<long long>()));
    }
}

void SetValuePropertyVisitor::visit(SignedIntegralPropertyInterface *property)
{
    if (m_variant.hasType<unsigned long long>())
    {
        assert(property->fromLongLong(m_variant.value<unsigned long long>()));
    }
    else if (m_variant.hasType<long long>())
    {
        assert(property->fromLongLong(m_variant.value<long long>()));
    }
}

void SetValuePropertyVisitor::visit(FloatingPointPropertyInterface *property)
{
    if (m_variant.hasType<unsigned long long>())
    {
        assert(property->fromDouble(m_variant.value<unsigned long long>()));
    }
    else if (m_variant.hasType<long long>())
    {
        assert(property->fromDouble(m_variant.value<long long>()));
    }
    else if (m_variant.hasType<double>())
    {
        assert(property->fromDouble(m_variant.value<double>()));
    }
}

void SetValuePropertyVisitor::visit(StringPropertyInterface *property)
{
    if (m_variant.hasType<std::string>())
    {
        assert(property->fromString(m_variant.value<std::string>()));
    }
}

void SetValuePropertyVisitor::visit(Property<glm::vec3> *property)
{
    if (m_variant.hasType<glm::vec3>())
    {
        property->setValue(m_variant.value<glm::vec3>());
    }
}

void SetValuePropertyVisitor::setVariant(const Variant & variant)
{
    m_variant = variant;
}

} // namespace reflectionzeug
