#include <iostream>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/PropertyDeserializer.h>
#include <reflectionzeug/PropertySerializer.h>

#include "PropertyExtension.h"
#include "SomeObject.h"

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

int main(int argc, char const *argv[])
{
    subscribeToChanges();
    iterateOverProperties();
    accessProperties();
    
    return 0;
}
