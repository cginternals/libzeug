#include <iostream>
#include <propertyzeug/Property.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/PropertyDeserializer.h>
#include <propertyzeug/PropertySerializer.h>
#include "SomeObject.h"

using namespace propertyzeug;

void createProperties()
{
    std::cout << ">> createProperties()" << std::endl;
    
    Property<unsigned long> property1("property1", "Property Title 1", 4815162342);
    
    bool value2 = true;
    Property<bool> property2("property2", "Property Title 2", [&value2]() {
        return value2;
    }, [&value2](const bool & value) {
        value2 = value;
    });
    
    property2.setAnnotations("This is an important property.");
    
    SomeObject object3;
    Property<int> property3("property3", "Property Title 3", object3, &SomeObject::count, &SomeObject::setCount);
}

void subscribeToChanges()
{
    std::cout << ">> subscribeToChanges()" << std::endl;
    
    Property<std::string> name("name", "Name", "Littlefinger");
    
    name.subscribe(events::kValueChanged, [](AbstractProperty & property) {
        auto name = property.to<Property<std::string>>();
        std::cout << name->value() << std::endl;
    });
    
    name.setValue("Tyrion Lannister");
    
    Property<char> gender("gender", "Gender", 'm');
    
    SomeObject object;
    gender.subscribe(events::kValueChanged, object, &SomeObject::propertyChanged);
    
    gender.setValue('f');
}

void createPropertyWithLimits()
{
    std::cout << ">> createPropertyWithLimits()" << std::endl;
    
    Property<float> size("size", "Size", 13.4);
    size.setMinimum(10.0);
    size.setMaximum(20.0);
}

void createStringPropertyWithChoices()
{
    std::cout << ">> createStringPropertyWithChoices()" << std::endl;
    
    Property<std::string> dragon("dragon", "Dragon", "Viserion");
    dragon.setChoices({ "Viserion", "Rhaegal" });
    dragon.addChoice("Drogon");
    
    for (const std::string & element: dragon.choices()) {
        std::cout << element << std::endl;
    }
    
    dragon.clearChoices();
}

void createPropertiesFromGroup()
{
    std::cout << ">> createPropertiesFromGroup()" << std::endl;
    
    SomeObject object;
    PropertyGroup group("rectangle", "Rectangle");
    group.addProperty<int>("x", "x", object, &SomeObject::count, &SomeObject::setCount);
    group.addProperty<int>("y", "y", 30);
    group.addProperty<int>("height", "Height", 200);
    
    std::cout << "Property Count: " << group.propertyCount() << std::endl;
}

void iterateOverProperties()
{
    std::cout << ">> iterateOverProperties()" << std::endl;
    
    PropertyGroup group("group", "Group");
    
    group.addProperty<float>("first", "First", 0.3f);
    group.addProperty(new PropertyGroup("second", "Second"));
    group.addProperty<unsigned long>("third", "Third", 7);
    group.addProperty(new PropertyGroup("fourth", "Fourth"));
    group.addProperty<Color>("fifth", "Fifth", Color(125, 125, 125));
    
    group.forEachValueProperty([](AbstractProperty & property) {
        std::cout << property.title() << std::endl;
    });

    group.forEachSubGroup([](PropertyGroup & group) {
        std::cout << group.title() << std::endl;
    });
}

void deserializeFromFile()
{
    std::cout << ">> deserializeFromFile()" << std::endl;
    
    PropertyGroup group("root", "Root");
    group.addProperty<int>("value1", "Value 1", 2);
    group.addProperty<float>("value2", "Value 2", 6);
    group.addProperty<bool>("failure", "Failure", false);
    group.addProperty<Color>("color", "Color", 0);
    group.addProperty<std::vector<int>>("vec3", "Vector 3", {12,4,54});
    
    group.addProperty(new PropertyGroup("group1", "Group 1"));
    group.subGroup("group1").addProperty<char>("value3", "Value3", 'a');
    group.subGroup("group1").addProperty<std::string>("name", "Name", "horst");
    group.subGroup("group1").addProperty<std::vector<bool>>("bool2", "Bool 2", {false,false});
    
    PropertyDeserializer deserializer;
    deserializer.deserialize(group, "examples/properties/data/group.ini");

    std::vector<int> vec3 = group.value<std::vector<int>>("vec3");
    std::cout << "Value of root/vec3: ";
    std::cout << "(" << vec3[0] << "," << vec3[1] << "," << vec3[2] << ")" << std::endl;
}

void accessProperties()
{
    std::cout << ">> accessProperties()" << std::endl;
    
    PropertyGroup root("root", "Root");
    PropertyGroup child("child", "Child");
    PropertyGroup childOfChild("childOfChild", "Child Of Child");
    root.addProperty(&child);
    child.addProperty(&childOfChild);
    childOfChild.addProperty("value", "Value", 42);
    
    std::cout << "Value of root/child/childOfChild/value: ";
    std::cout << root.value<int>("child/childOfChild/value") << std::endl;
}

void serializeToFile()
{
    std::cout << ">> serializeFromFile()" << std::endl;
    
    PropertyGroup group("root", "Root");
    group.addProperty<int>("value1", "Value 1", 2);
    group.addProperty<float>("value2", "Value 2", 6.2);
    group.addProperty<bool>("failure", "Failure", false);
    group.addProperty<Color>("color", "Color", Color(42,244,123));
    group.addProperty<std::vector<int>>("vec3", "Vector 3", {1,2,3});
    group.addProperty<std::vector<bool>>("bvec2", "Bool Vector 2", {true, false});
    
    PropertyGroup group1("group1", "Group 1");
    group.addProperty(&group1);

    group1.addProperty<char>("value3", "Value3", 'a');
    group1.addProperty<std::string>("name", "Name", "horst");
    
    PropertyGroup group2("group2", "Group 2");
    group1.addProperty(&group2);
    
    group2.addProperty<std::string>("city", "City", "Potsdam");
    
    PropertySerializer serializer;
    serializer.serialize(group, "examples/properties/data/groupOut.ini");
}

void useVectorProperties()
{
    std::cout << ">> useVectorProperties()" << std::endl;
    
    Property<std::vector<int>> ivec3("ivec3", "Integer Vector 3", {1,2,3});
    std::cout << "ivec3.fixedSize() = " << ivec3.fixedSize() << std::endl;
    
    Property<std::vector<float>> mat2x2("mat2x2", "Matrix 2x2", {1.1, 2.2, 3.3, 4.4});
    std::cout << "mat2x2.fixedSize() = " << mat2x2.fixedSize() << std::endl;
    mat2x2.setDimensions({2,2});
    
    std::vector<bool> mat = {
        true,  false, false, false,
        false, true,  false, false,
        false, false, true,  false
    };
    Property<std::vector<bool>> mat4x3("mat4x3", "Bool Matrix 4x3", mat);
    std::cout << "mat4x3.fixedSize() = " << mat4x3.fixedSize() << std::endl;
}

int main(int argc, char const *argv[])
{
    createProperties();
    subscribeToChanges();
    createPropertyWithLimits();
    createStringPropertyWithChoices();
    createPropertiesFromGroup();
    iterateOverProperties();
    deserializeFromFile();
    serializeToFile();
    accessProperties();
    useVectorProperties();
    
    return 0;
}