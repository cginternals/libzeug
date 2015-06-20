
#include <reflectionzeug/tools/DeserializerJSON.h>

#include <reflectionzeug/tools/JSONReader.h>


namespace reflectionzeug {


DeserializerJSON::DeserializerJSON()
{
}

DeserializerJSON::~DeserializerJSON()
{
}

bool DeserializerJSON::fromString(Variant & obj, const std::string & string)
{
    JSONReader reader;
    return reader.parse(string, obj);
}


} // namespace reflectionzeug
