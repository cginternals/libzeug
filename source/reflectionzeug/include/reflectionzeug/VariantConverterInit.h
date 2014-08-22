
#pragma once

#include <sstream>

#include <reflectionzeug/Variant2.h>
#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/util.h>


namespace reflectionzeug
{

template <typename ValueType, typename = void>
struct VariantConverterInit
{
    void operator()()
    {
    }
};

template <>
struct VariantConverterInit<bool>
{
    void operator()()
    {
        Variant2::registerConverter<bool, char>();
        Variant2::registerConverter<bool, unsigned char>();
        Variant2::registerConverter<bool, short>();
        Variant2::registerConverter<bool, unsigned short>();
        Variant2::registerConverter<bool, int>();
        Variant2::registerConverter<bool, unsigned int>();
        Variant2::registerConverter<bool, long>();
        Variant2::registerConverter<bool, unsigned long>();
        Variant2::registerConverter<bool, long long>();
        Variant2::registerConverter<bool, unsigned long long>();
        Variant2::registerConverter<bool, float>();
        Variant2::registerConverter<bool, double>();
        Variant2::registerConverter<bool, long double>();

        Variant2::registerConverter<bool, float>();
        Variant2::registerConverter<bool, double>();
        Variant2::registerConverter<bool, long double>();

        Variant2::registerConverter<bool, std::string>(toString);
    }

    static bool toString(bool value)
    {
        return value ? "true" : "false";
    }
};

template <typename ValueType>
struct VariantConverterInit<ValueType, EnableIf<isIntegral<ValueType>>>
{
    void operator()()
    {
        Variant2::registerConverter<ValueType, bool>(toBool);

        Variant2::registerConverter<ValueType, char>();
        Variant2::registerConverter<ValueType, unsigned char>();
        Variant2::registerConverter<ValueType, short>();
        Variant2::registerConverter<ValueType, unsigned short>();
        Variant2::registerConverter<ValueType, int>();
        Variant2::registerConverter<ValueType, unsigned int>();
        Variant2::registerConverter<ValueType, long>();
        Variant2::registerConverter<ValueType, unsigned long>();
        Variant2::registerConverter<ValueType, long long>();
        Variant2::registerConverter<ValueType, unsigned long long>();

        Variant2::registerConverter<ValueType, float>();
        Variant2::registerConverter<ValueType, double>();
        Variant2::registerConverter<ValueType, long double>();

        Variant2::registerConverter<ValueType, std::string>(util::toString<ValueType>);
    }

    static bool toBool(const ValueType & value)
    {
        return value != 0;
    }
};

template <typename ValueType>
struct VariantConverterInit<ValueType, EnableIf<std::is_floating_point<ValueType>>>
{
    void operator()()
    {
        Variant2::registerConverter<ValueType, float>();
        Variant2::registerConverter<ValueType, double>();
        Variant2::registerConverter<ValueType, long double>();
        Variant2::registerConverter<ValueType, std::string>(util::toString<ValueType>);
    }
};

template <>
struct VariantConverterInit<std::string>
{
    void operator()()
    {
        Variant2::registerConverter<std::string, bool>(toBool);

        Variant2::registerConverter<std::string, char>(util::fromString<char>);
        Variant2::registerConverter<std::string, unsigned char>(util::fromString<unsigned char>);
        Variant2::registerConverter<std::string, short>(util::fromString<short>);
        Variant2::registerConverter<std::string, unsigned short>(util::fromString<unsigned short>);
        Variant2::registerConverter<std::string, int>(util::fromString<int>);
        Variant2::registerConverter<std::string, unsigned int>(util::fromString<unsigned int>);
        Variant2::registerConverter<std::string, long>(util::fromString<long>);
        Variant2::registerConverter<std::string, unsigned long>(util::fromString<unsigned long>);
        Variant2::registerConverter<std::string, long long>(util::fromString<long long>);
        Variant2::registerConverter<std::string, unsigned long long>(util::fromString<unsigned long long>);

        Variant2::registerConverter<std::string, float>(util::fromString<float>);
        Variant2::registerConverter<std::string, double>(util::fromString<double>);
        Variant2::registerConverter<std::string, long double>(util::fromString<long double>);
    }

    static bool toBool(const std::string & string)
    {
        return !string.empty();
    }
};

template <>
struct VariantConverterInit<VariantArray>
{
    void operator()()
    {
        Variant2::registerConverter<VariantArray, std::string>(toString);
    }

    static std::string toString(const VariantArray & array)
    {
        if (array.empty())
            return "[]";
            
        std::stringstream stream;
        stream << "[";

        for (auto it = array.begin(); it != array.end(); ++it)
        {
            if (it->hasType<VariantArray>() || it->hasType<VariantMap>())
                stream << it->value<std::string>();
            else
                stream << "\"" << it->value<std::string>() << "\"";

            if (it != --array.end())
                stream << ", ";
        }

        stream << "]";
        return stream.str();
    }
};

template <>
struct VariantConverterInit<VariantMap>
{
    void operator()()
    {
        Variant2::registerConverter<VariantMap, std::string>(toString);
    }

    static std::string toString(const VariantMap & map)
    {
        if (map.empty())
            return "{}";

        std::stringstream stream;
        stream << "{";

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            stream << "\"" << it->first << "\": ";

            if (it->second.hasType<VariantArray>() || it->second.hasType<VariantMap>())
                stream << it->second.value<std::string>();
            else
                stream << "\"" << it->second.value<std::string>() << "\"";

            if (it != --map.end())
                stream << ", ";
        }

        stream << "}";
        return stream.str();
    }
};

} // namespace reflectionzeug
