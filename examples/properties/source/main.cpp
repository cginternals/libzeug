#include <iostream>
#include <propertyzeug/Attribute.h>

using namespace propertyzeug;

int main(int argc, char const *argv[])
{
    std::cout << "it works!" << std::endl;
    
    
    BaseAttribute<int> * attr = new BaseAttribute<int>("name", "title", 2);
    BaseAttribute<int> * attr2 = new BaseAttribute<int>("name2", "title2", [](){return 3;}, [](int){});
    
    std::cout << attr->name() << std::endl;
    std::cout << attr->title() << std::endl;
    std::cout << attr->value() << std::endl;
    
    std::cout << attr2->value() << std::endl;
    
    delete attr;
    delete attr2;
    
    BaseAttribute<int> apple("apple", "Apple", 4);
    apple.subscribe(BaseAttribute<int>::kTitleChanged, [](AbstractAttribute &) {
        std::cout << "Title changed!" << std::endl;
    });
    
    apple.setTitle("Appoel");
    
    Attribute<int> * banana = new Attribute<int>("banana", "Banana", 5);
    std::cout << banana->value();
    
    return 0;
}