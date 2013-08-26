
#pragma once

#include <fstream>
#include <propertyzeug/Property.h>
#include "AbstractPropertyVisitor.h"

namespace propertyzeug {
    
/** @brief
 * Saves values of a property hierachy to a specified file.
 */
    
class PROPERTYZEUG_API PropertySerializer : public AbstractPropertyVisitor
{
public:
    PropertySerializer();
    virtual ~PropertySerializer();

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<unsigned int> & property);
    virtual void visit(Property<long> & property);
    virtual void visit(Property<unsigned long> & property);
    virtual void visit(Property<char> & property);
    virtual void visit(Property<unsigned char> & property);
    virtual void visit(Property<float> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);

    virtual void visit(PropertyGroup & property);

    bool serialize(PropertyGroup & group, std::string filePath);
    
protected:
    template <typename Type>
    void convertPrimitiveProperty(const Property<Type> & property);

    std::fstream m_fstream;
    std::string m_currentPath;
};
    
template <typename Type>
void PropertySerializer::convertPrimitiveProperty(const Property<Type> & property)
{
    assert(m_fstream.is_open());
    m_fstream << m_currentPath << property.name() << "=" << property.value() << std::endl;
}
    
} // namespace