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
    
    Property<int> property1("property1", 4815162342);
    
    bool value2 = true;
    Property<bool> property2("property2", [&value2]() {
        return value2;
    }, [&value2](const bool & value) {
        value2 = value;
    });
    
    property2.setAnnotations("This is an important property.");
    
    SomeObject object3;
    Property<int> property3("property3", object3, &SomeObject::count, &SomeObject::setCount);
}

void subscribeToChanges()
{
    std::cout << ">> subscribeToChanges()" << std::endl;
    
    Property<std::string> name("name", "Littlefinger");
    
    name.subscribe(events::kValueChanged, [](AbstractProperty & property) {
        auto name = property.to<Property<std::string>>();
        std::cout << name->value() << std::endl;
    });
    
    name.setValue("Tyrion Lannister");
    
    Property<int> gender("gender", 12);
    
    SomeObject object;
    gender.subscribe(events::kValueChanged, object, &SomeObject::propertyChanged);
    
    gender.setValue(13);
}

void createPropertyWithLimits()
{
    std::cout << ">> createPropertyWithLimits()" << std::endl;
    
    Property<double> size("size", 13.4);
    size.setMinimum(10.0);
    size.setMaximum(20.0);
}

void createStringPropertyWithChoices()
{
    std::cout << ">> createStringPropertyWithChoices()" << std::endl;
    
    Property<std::string> dragon("dragon", "Viserion");

	std::string choices[] = {"Viserion", "Rhaegal"};
    dragon.setChoices(std::vector<std::string>(std::begin(choices), std::end(choices)));
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
    PropertyGroup group("rectangle");
    group.addProperty<int>("x", object, &SomeObject::count, &SomeObject::setCount);
    group.addProperty<int>("y", 30);
    group.addProperty<int>("height", 200);
    
    std::cout << "Property Count: " << group.propertyCount() << std::endl;
}

void iterateOverProperties()
{
    std::cout << ">> iterateOverProperties()" << std::endl;
    
    PropertyGroup group("group");
    
    group.addProperty<double>("first", 0.3f);
    group.addGroup("second");
    group.addProperty<int>("third", 7);
    group.addGroup("fourth");
    group.addProperty<Color>("fifth", Color(125, 125, 125));
    
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
    
    PropertyGroup group("root");
    group.addProperty<int>("value1", 2);
    group.addProperty<double>("value2", 6);
    group.addProperty<bool>("failure", false);
    group.addProperty<Color>("color", Color(125, 125, 0));

	int vec3[] = {12, 4, 54};
    group.addProperty<std::vector<int>>("vec3", std::vector<int>(std::begin(vec3), std::end(vec3)));
    
    group.addGroup("group1");
    group.group("group1")->addProperty<int>("value3", 143);
    group.group("group1")->addProperty<std::string>("name", "horst");

	int bool2[] = {false, false};
    group.group("group1")->addProperty<std::vector<bool>>("bool2", std::vector<bool>(std::begin(bool2), std::end(bool2)));

	int vec4[] = {0, 0, 0, 0};
    group.group("group1")->addProperty<std::vector<int>>("vec4", std::vector<int>(std::begin(vec4), std::end(vec4)));
    
    PropertyDeserializer deserializer;
    deserializer.deserialize(group, "examples/properties/data/group.ini");

    Property<std::vector<int>> * vectorProperty = group.property<std::vector<int>>("group1/vec3");
    std::cout << "Value of root/group1/vec3: ";
    std::cout << vectorProperty->valueAsString() << std::endl;
}

void accessProperties()
{
    std::cout << ">> accessProperties()" << std::endl;
    
    PropertyGroup root("root");
    PropertyGroup child("child");
    PropertyGroup childOfChild("childOfChild");
    root.addProperty(&child);
    child.addProperty(&childOfChild);
    childOfChild.addProperty("answer", 42);
    
    std::cout << "Value of root/child/childOfChild/answer: ";
    std::cout << root.value<int>("child/childOfChild/answer") << std::endl;
}

void serializeToFile()
{
    std::cout << ">> serializeFromFile()" << std::endl;
    
    PropertyGroup group("root");
    group.addProperty<int>("value1", 2);
    group.addProperty<double>("value2", 6.2);
    group.addProperty<bool>("failure", false);
    group.addProperty<Color>("color", Color(42,244,123));

	int vec3[] = {1, 2, 3};
    group.addProperty<std::vector<int>>("vec3", std::vector<int>(std::begin(vec3), std::end(vec3)));

    group.addProperty<std::vector<bool>>("bvec2", std::vector<bool>(2, true));
    
    PropertyGroup group1("group1");
    group.addProperty(&group1);

    group1.addProperty<int>("value3", 143);
    group1.addProperty<std::string>("name", "horst");
    
    PropertyGroup group2("group2");
    group1.addProperty(&group2);
    
    group2.addProperty<std::string>("city", "Potsdam");
    
    PropertySerializer serializer;
    serializer.serialize(group, "examples/properties/data/groupOut.ini");
}

void useVectorProperties()
{
    std::cout << ">> useVectorProperties()" << std::endl;
    
	int ivec3[] = {1, 2, 3};
    Property<std::vector<int>> ivec3Property("ivec3", std::vector<int>(std::begin(ivec3), std::end(ivec3)));
    std::cout << "ivec3.fixedSize() = " << ivec3Property.fixedSize() << std::endl;
    
	double mat2x2[] = {1.1, 2.2, 3.3, 4.4};
    Property<std::vector<double>> mat2x2Property("mat2x2", std::vector<double>(std::begin(mat2x2), std::end(mat2x2)));
    std::cout << "mat2x2.fixedSize() = " << mat2x2Property.fixedSize() << std::endl;
    mat2x2Property.setDimensions(2, 2);
    
    bool mat4x3[] = {
        true,  false, false, false,
        false, true,  false, false,
        false, false, true,  false
    };
    Property<std::vector<bool>> mat4x3Property("mat4x3", std::vector<bool>(std::begin(mat4x3), std::end(mat4x3)));
    std::cout << "mat4x3.fixedSize() = " << mat4x3Property.fixedSize() << std::endl;
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
