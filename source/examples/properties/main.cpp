
#include <cstdio>
#include <iostream>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/PropertyDeserializer.h>
#include <reflectionzeug/PropertySerializer.h>

#include "PropertyExtension.h"
#include "SomeObject.h"

#ifdef WIN32
#define INI_PATH "data\\properties.ini"
#else
#define INI_PATH "data/properties.ini"
#endif

using namespace reflectionzeug;

void subscribeToChanges()
{
    std::cout << ">> subscribeToChanges()" << std::endl;
    
    Property<std::string> * name = new Property<std::string>("name", "Littlefinger");
    
    name->valueChanged.connect([] (const std::string & string) {
        std::cout << "Value Changed to \"" << string << "\"" << std::endl;
    });
    
    name->setValue("Tyrion Lannister");
    
    Property<int> * number = new Property<int>("number", 12);
    
    SomeObject object;
    number->valueChanged.connect(&object, &SomeObject::valueChanged);
    
    number->setValue(13);

    delete name;
    delete number;
}

void iterateOverProperties()
{
    std::cout << ">> iterateOverProperties()" << std::endl;
    
    PropertyGroup * group = new PropertyGroup("group");
    
    group->addProperty<double>("first", 0.3);
    group->addGroup("second");
    group->addProperty<int>("third", 7);
    group->addGroup("fourth");
    group->addProperty<Color>("fifth", Color(125, 125, 125));
    group->addProperty<std::vector<int>>("sixth", { 1, 2, 3 });
    
    group->forEachValueProperty([](AbstractProperty & property) {
        std::cout << property.title() << std::endl;
    });

    group->forEachSubGroup([](PropertyGroup & subGroup) {
        std::cout << subGroup.title() << std::endl;
    });

    delete group;
}

void accessProperties()
{
    std::cout << ">> accessProperties()" << std::endl;
    
    PropertyGroup * root = new PropertyGroup("root");
    auto * subGroup = root->addGroup("subGroup");
    auto * property = subGroup->addProperty<int>("value", 12);
    
    std::cout << "Value of root/subGroup/value: ";
    std::cout << root->value<int>("subGroup/value") << std::endl;
}

bool saveProperties()
{
    std::cout << ">> saveProperties()" << std::endl;
    
    PropertyGroup root("root");
    
    root.addProperty<std::vector<double>>("normal", { -1.3, 2.6, -4.2 });
    root.addProperty<bool>("eatable", true);
    
    PropertyGroup * subGroup = root.addGroup("more");
    
    subGroup->addProperty<Color>("spinach_green", Color(74, 84, 43));
    subGroup->addProperty<int>("apple_count", 17);
    
    PropertySerializer serializer;
    return serializer.serialize(root, INI_PATH);
}

bool loadProperties()
{
    PropertyGroup root("root");
    
    root.addProperty<std::vector<double>>("normal", { 0.0, 0.0, 0.0 });
    root.addProperty<bool>("eatable", false);
    
    PropertyGroup * subGroup = root.addGroup("more");
    
    subGroup->addProperty<Color>("spinach_green", Color());
    subGroup->addProperty<int>("apple_count", 0);
    
    PropertyDeserializer deserializer;
    if (!deserializer.deserialize(root, INI_PATH))
        return false;
    
    
    std::cout << root.name() << std::endl;
    
    root.forEachValueProperty([] (ValueProperty & property)
    {
        std::cout << property.path() << " = " << property.toString() << std::endl;
    });
    
    std::cout << subGroup->path() << std::endl;
    
    subGroup->forEachValueProperty([] (ValueProperty & property)
    {
        std::cout << property.path() << " = " << property.toString() << std::endl;
    });
    
    return true;
}

int main(int argc, char const *argv[])
{
    subscribeToChanges();
    iterateOverProperties();
    accessProperties();
    
    if (saveProperties() && loadProperties());
        std::remove(INI_PATH);
    
    return 0;
}
