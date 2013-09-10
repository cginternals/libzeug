
#include <iostream>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/PropertySerializer.h>

namespace propertyzeug {
    
PropertySerializer::PropertySerializer()
:   m_currentPath("")
{
}

PropertySerializer::~PropertySerializer()
{
}
    
bool PropertySerializer::serialize(PropertyGroup & group, std::string filePath)
{
    m_fstream.open(filePath, std::ios_base::out);
    
    if (!m_fstream.is_open()) {
        std::cerr << "Could not write to file \"" << filePath << "\"" << std::endl;
        return false;
    }
    
    m_fstream << "[" << group.name() << "]" << std::endl;
    m_currentPath = "";
    group.forEachValueProperty([this](AbstractProperty & property) {
        property.accept(*this);
    });
    
    m_fstream << std::endl;
    
    group.forEachSubGroup([this](PropertyGroup & subGroup) {
        m_fstream << "[" << subGroup.name() << "]" << std::endl;
        m_currentPath = "";
        subGroup.forEachProperty([this](AbstractProperty & property) {
            property.accept(*this);
        });
        m_fstream << std::endl;
    });
    
    
    m_fstream.close();
    return true;
}
    
void PropertySerializer::serializeProperty(const AbstractProperty & property,
    const std::function<std::string()> & valueFunctor)
{
    assert(m_fstream.is_open());
    m_fstream << m_currentPath << property.name();
    m_fstream << "=" << valueFunctor() << std::endl;
}

void PropertySerializer::visit(Property<bool> & property)
{
    this->serializeProperty(property, [&property]() {
        return property.valueAsString();
    });
}

void PropertySerializer::visit(Property<int> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<unsigned int> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<long> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<unsigned long> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<char> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<unsigned char> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<float> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<double> & property)
{
    this->serializePrimitiveProperty(property);
}

void PropertySerializer::visit(Property<std::string> & property)
{
    this->serializeProperty(property, [&property]() {
        return property.value();
    });
}

void PropertySerializer::visit(Property<Color> & property)
{
    this->serializeProperty(property, [&property]() {
        return property.valueAsString();
    });
}

void PropertySerializer::visit(Property<FilePath> & property)
{
    assert(m_fstream.is_open());
    m_fstream << m_currentPath << property.name() << "=";
    m_fstream << property.value().string() << std::endl;
}

void PropertySerializer::visit(Property<std::vector<bool>> & property)
{
    this->serializeProperty(property, [&property]() {
        return property.valueAsString();
    });
}

void PropertySerializer::visit(Property<std::vector<int>> & property)
{
    this->serializeVectorProperty(property);
}

void PropertySerializer::visit(Property<std::vector<float>> & property)
{
    this->serializeVectorProperty(property);
}

void PropertySerializer::visit(Property<std::vector<double>> & property)
{
    this->serializeVectorProperty(property);
}

void PropertySerializer::visit(PropertyGroup & property)
{
    std::string oldPath = m_currentPath;
    m_currentPath += property.name() + "/";
    property.forEachProperty([this](AbstractProperty & property) {
        property.accept(*this);
    });
    m_currentPath = oldPath;
}

} // namespace