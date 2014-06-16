
#pragma once


namespace reflectionzeug
{

template <typename ValueType, typename ConversionType>
bool implicitConverter(const ValueType & input, ConversionType * output)
{
    *output = input;
    return true;
}

} // namespace reflectionzeug
