#include <iostream>
#include <propertyzeug/BaseAttribute.h>

using namespace propertyzeug;

int main(int argc, char const *argv[])
{
    std::cout << "it works!" << std::endl;
    
    
    BaseAttribute<int> * attr = new BaseAttribute<int>("name", "title", 2);
    
    std::cout << attr->name() << std::endl;
    std::cout << attr->title() << std::endl;
    std::cout << attr->value() << std::endl;
    
    delete attr;
    
    return 0;
}