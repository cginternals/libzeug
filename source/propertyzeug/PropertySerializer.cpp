
#include <iostream>
#include <propertyzeug/PropertySerializer.h>

namespace propertyzeug {
    
PropertySerializer::PropertySerializer()
{
}

PropertySerializer::~PropertySerializer()
{
}
    
bool PropertySerializer::serialize(PropertyGroup & group, std::string filePath)
{
    std::cout << "Serialize group" << std::endl;
    return false;
}

void PropertySerializer::visit(Property<bool> & property)
{

}

void PropertySerializer::visit(Property<int> & property)
{

}

void PropertySerializer::visit(Property<unsigned int> & property)
{

}

void PropertySerializer::visit(Property<long> & property)
{

}

void PropertySerializer::visit(Property<unsigned long> & property)
{

}

void PropertySerializer::visit(Property<char> & property)
{

}

void PropertySerializer::visit(Property<unsigned char> & property)
{

}

void PropertySerializer::visit(Property<float> & property)
{

}

void PropertySerializer::visit(Property<double> & property)
{

}

void PropertySerializer::visit(Property<std::string> & property)
{

}

void PropertySerializer::visit(Property<Color> & property)
{

}

void PropertySerializer::visit(Property<FilePath> & property)
{

}

void PropertySerializer::visit(PropertyGroup & property)
{

}

} // namespace