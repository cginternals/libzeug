
#include <iostream>

#include <reflectionzeug/property/Property.h>
#include <reflectionzeug/property/PropertyGroup.h>
#include <reflectionzeug/tools/SerializerINI.h>
#include <reflectionzeug/tools/SerializerJSON.h>
#include <reflectionzeug/base/util.h>

#include "MyObject.h"


#define INI_PATH "properties.ini"


using namespace reflectionzeug;


void accessingProperties();
void iteratingThroughProperties();
void subscribingToChanges();
void typeDeduction();
void serializingProperties();
void printGroup(const PropertyGroup & group, const std::string & path = "");


int main(int argc, char const *argv[])
{
    /*
    accessingProperties();
    iteratingThroughProperties();
    subscribingToChanges();
    typeDeduction();
    */
    serializingProperties();

    return 0;
}

void accessingProperties()
{
    auto object = MyObject{};

    // Access its value directly.
    auto intValue = object.value<int>("int_value");
    intValue += 10;
    object.setValue<int>("int_value", intValue);

    // Retrieve a generic AbstractProperty.
    AbstractProperty * enumProperty = object.property("enum_value");

    // Access a nested property.
    Property<bool> * boolProperty = object.property("sub_group/bool_value")->as<Property<bool>>();

    // Access by index.
    AbstractProperty * property = object.at(1);
    std::cout << property->name() << std::endl; // >> "enum_value"
}

void iteratingThroughProperties()
{
    auto object = MyObject{};

    object.forEach([] (AbstractProperty & property)
        {
            std::cout << property.name() << std::endl;
        });
    // >> "int_value" \n "enum_value" \n "float_array" \n "sub_group" \n

/*
    object.forEachValue([] (AbstractValueProperty & property)
        {
            std::cout << property.toString() << std::endl;
        });
*/
    // >> -13 \n Value1 \n (0.5, 1, 0.3) \n
}

void subscribingToChanges()
{
    auto object = MyObject{};

    Property<int> * intProperty = object.property("int_value")->as<Property<int>>();

    // Subscribe to updates of a property
    intProperty->valueChanged.connect(
        [] (const int & value)
        {
            std::cout << value << std::endl;
        });

    object.setValue<int>("int_value", 36);
    // >> 36 \n
}

void typeDeduction()
{
    auto object = MyObject{};

    AbstractProperty * property = object.property("float_array");

    // Deduce a property's type via its type() method.
    if (property->type() == typeid(std::array<float, 3>))
    {
        std::cout << property->name() << " is of type std::array<float, 3>." << std::endl;
    }
}

void serializingProperties()
{
    {
        auto object = MyObject{};
        object.setValue<int>("int_value", -1);
        object.setValue<MyEnum>("enum_value", MyEnum::Value3);
        object.setValue<std::array<float, 3>>("float_array", {{ 4.8f, 15.16f, 23.42f }});
        object.setValue<bool>("sub_group/bool_value", false);
        
        // Serialize property hierarchies ...
        try {
            SerializerINI serializer;
            serializer.save(object.toVariant(), INI_PATH);
        }
        catch (...)
        {
        }
    }

    {
        auto object = MyObject{};

        try {
            // ... and deserialize them.
            SerializerINI serializer;

            Variant values;
            serializer.load(values, INI_PATH);
            SerializerJSON json(SerializerJSON::Beautify);
            std::cout << json.toString(values) << "\n";

            object.fromVariant(values);
            printGroup(object);
        }
        catch (...)
        {
        }
    }
}

void printGroup(const PropertyGroup & group, const std::string & path)
{
    std::string groupPath = path + group.name() + "/";
    std::cout << groupPath << std::endl;

/*
    group.forEachValue([&groupPath] (const AbstractValueProperty & property)
    {
        std::cout << groupPath + property.name() << " = " << property.toString() << std::endl;
    });
*/

    group.forEach([&groupPath] (const AbstractProperty & property)
    {
        if (!property.isGroup()) {
            std::cout << groupPath + property.name() << " = " << property.toString() << std::endl;
        }
    } );

    group.forEachGroup([&groupPath] (const PropertyGroup & subGroup)
    {
        printGroup(subGroup, groupPath + "/");
    });
}
