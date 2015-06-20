
#include <reflectionzeug/tools/Deserializer.h>

#include <fstream>
#include <sstream>


namespace reflectionzeug {


Deserializer::Deserializer()
{
}

Deserializer::~Deserializer()
{
}

bool Deserializer::load(Variant & obj, const std::string & filename)
{
    // Open file
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (!in) {
        // Could not open file
        return false;
    }

    // Read file content
    std::string content;
    in.seekg(0, std::ios::end);
    content.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&content[0], content.size());
    in.close();

    // Parse string
    return fromString(obj, content);
}


} // namespace reflectionzeug
