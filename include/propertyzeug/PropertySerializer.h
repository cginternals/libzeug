
#pragma once

#include <sstream>
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

    virtual void visit(Property<std::vector<bool>> & property);
    virtual void visit(Property<std::vector<int>> & property);
    virtual void visit(Property<std::vector<float>> & property);
    virtual void visit(Property<std::vector<double>> & property);

    virtual void visit(PropertyGroup & property);

    bool serialize(PropertyGroup & group, std::string filePath);
    
protected:
    void serializeProperty(const AbstractProperty & property,
                           std::function<std::string()> valueFunctor);
    
    template <typename Type>
    void serializePrimitiveProperty(const Property<Type> & property);
    
    template <typename Type>
    void serializeVectorProperty(const Property<Type> & property);

    std::fstream m_fstream;
    std::string m_currentPath;
};
    
template <typename Type>
void PropertySerializer::serializePrimitiveProperty(const Property<Type> & property)
{
    this->serializeProperty(property, [&property]() -> std::string {
        std::stringstream stream;
        stream << property.value();
        return stream.str();
    });
}
    
template <typename Type>
void PropertySerializer::serializeVectorProperty(const Property<Type> & property)
{
    this->serializeProperty(property, [&property]() {
        std::stringstream stream;
        stream << "(";
        for(auto e = property.value().begin(); e < --property.value().end(); e++) {
            stream << *e << ",";
        }
        stream << property.value().back();
        stream << ")";
        
        return stream.str();
    });
}
    
} // namespace