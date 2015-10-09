#include <iostream>

#include <reflectionzeug/base/Color.h>
#include <reflectionzeug/variant/Variant.h>


using namespace reflectionzeug;

int main(int argc, char *argv[])
{
    /** Create a Variant that stores a VariantMap without copying.
     * (VariantArray is equivalent)
     */
    {
    Variant map = Variant::map();
    map.asMap()->insert({ "method", Variant(1) });
    
    std::cout << map.value<std::string>() << std::endl;
    }
    
    {
    VariantMap map({{ "method", Variant(2) }});
    Variant variant(move(map));
    
    std::cout << variant.value<std::string>() << std::endl;
    }
    
    /** Create a Variant that stores a long integer and check possible conversions. */
    {
    Variant variant(5583l);
    
    std::cout << (variant.hasType<long>() ? "true" : "false") << std::endl;
    
    /** Standard implicit conversions are supported. */
    std::cout << (variant.canConvert<bool>() ? "true" : "false") << std::endl;
    
    /** Every numerical can also be converted to std::string. */
    std::cout << (variant.canConvert<std::string>() ? "true" : "false") << std::endl;
    }
    
    /** Store an arbitrary value */
    {
    Variant variant = Variant::fromValue(Color(128, 128, 0));
    
    std::cout << (variant.hasType<Color>() ? "true" : "false") << std::endl;
    std::cout << (variant.canConvert<std::string>() ? "true" : "false") << std::endl;
    }
}
