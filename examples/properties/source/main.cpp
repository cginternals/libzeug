#include <iostream>
#include <propertyzeug/AbstractAttribute.h>

using namespace propertyzeug;

int main(int argc, char const *argv[])
{
    std::cout << "it works!" << std::endl;
    
    
    AbstractAttribute * attr = new AbstractAttribute("name", "title");
    
    std::cout << attr->name() << std::endl;
    std::cout << attr->title() << std::endl;
    
    delete attr;
    
    return 0;
}