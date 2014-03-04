
#pragma once


namespace reflectionzeug
{

template <typename Type>
Type PropertyDeserializer::convertString(const std::string & stringValue)
{
    std::stringstream stream(stringValue);
    Type value;
    stream >> value;
    return value;
}

} // namespace reflectionzeug
