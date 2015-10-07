
#include <stringzeug/conversion.h>


namespace stringzeug
{


template <>
char fromString<char>(const std::string & string)
{
    std::stringstream stream(string);
    int value;
    stream >> value;
    return static_cast<char>(value);
}

template <>
unsigned char fromString<unsigned char>(const std::string & string)
{
    std::stringstream stream(string);
    unsigned int value;
    stream >> value;
    return static_cast<unsigned char>(value);
}

template <>
std::string toString<char>(const char & value)
{
    std::stringstream stream;
    stream << static_cast<int>(value);
    return stream.str();
}

template <>
std::string toString<unsigned char>(const unsigned char & value)
{
    std::stringstream stream;
    stream << static_cast<unsigned int>(value);
    return stream.str();
}


} // namespace stringzeug
