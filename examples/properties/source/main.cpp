#include <iostream>
#include <propertyzeug/Property.h>
#include <propertyzeug/Color.h>
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

int main(int argc, char const *argv[])
{
    createProperties();
    subscribeToChanges();
    
    return 0;
}