
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
    
    group.forEachSubGroup([this](PropertyGroup & subGroup) {
        m_fstream << "[" << subGroup.name() << "]" << std::endl;
        m_currentPath = "";
        subGroup.forEachProperty([this](AbstractProperty & property) {
            property.accept(*this);
        });
    });
    
    
    m_fstream.close();
    return true;
}

void PropertySerializer::visit(Property<bool> & property)
{
    assert(m_fstream.is_open());
    std::string value = property.value() ? "true" : "false";
    m_fstream << property.name() << "=" << value << std::endl;
}

void PropertySerializer::visit(Property<int> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<unsigned int> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<long> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<unsigned long> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<char> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<unsigned char> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<float> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<double> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<std::string> & property)
{
    this->convertPrimitiveProperty(property);
}

void PropertySerializer::visit(Property<Color> & property)
{
    assert(m_fstream.is_open());
    m_fstream << m_currentPath << property.name() << "=";
    m_fstream << "(";
    m_fstream << property.value().red() << ",";
    m_fstream << property.value().green() << ",";
    m_fstream << property.value().blue() << ",";
    m_fstream << property.value().alpha();
    m_fstream << ")" << std::endl;
}

void PropertySerializer::visit(Property<FilePath> & property)
{
    assert(m_fstream.is_open());
    m_fstream << m_currentPath << property.name() << "=";
    m_fstream << property.value().string() << std::endl;
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