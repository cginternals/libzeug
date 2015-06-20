
#include <reflectionzeug/tools/Serializer.h>

#include <fstream>
#include <sstream>


namespace reflectionzeug {


Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

bool Serializer::save(const Variant & obj, const std::string & filename)
{
    // Open file
    std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!out) {
        // Could not open file
        return false;
    }

    // Write string representation to file
    out << toString(obj);
    out.close();

    // Success
    return true;
}


} // namespace reflectionzeug
