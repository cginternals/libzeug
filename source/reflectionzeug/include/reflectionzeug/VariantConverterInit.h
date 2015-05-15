#pragma once

#include <sstream>

#include <reflectionzeug/Variant.h>
#include <reflectionzeug/specialization_helpers.h>
#include <reflectionzeug/util.h>
#include <reflectionzeug/FilePath.h>
#include <reflectionzeug/EnumDefaultStrings.h>
#include <reflectionzeug/Color.h>

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
        Variant::registerConverter<bool, char>();
        Variant::registerConverter<bool, unsigned char>();
        Variant::registerConverter<bool, short>();
        Variant::registerConverter<bool, unsigned short>();
        Variant::registerConverter<bool, int>();
        Variant::registerConverter<bool, unsigned int>();
        Variant::registerConverter<bool, long>();
        Variant::registerConverter<bool, unsigned long>();
        Variant::registerConverter<bool, long long>();
        Variant::registerConverter<bool, unsigned long long>();
        Variant::registerConverter<bool, float>();
        Variant::registerConverter<bool, double>();
        Variant::registerConverter<bool, long double>();

        Variant::registerConverter<bool, float>();
        Variant::registerConverter<bool, double>();
        Variant::registerConverter<bool, long double>();

        Variant::registerConverter<bool, std::string>(toString);
    }

    static std::string toString(bool value)
    {
        return value ? "true" : "false";
    }
};

template <typename ValueType>
struct VariantConverterInit<ValueType, EnableIf<isIntegral<ValueType>>>
{
    void operator()()
    {
        Variant::registerConverter<ValueType, bool>(toBool);

        Variant::registerConverter<ValueType, char>();
        Variant::registerConverter<ValueType, unsigned char>();
        Variant::registerConverter<ValueType, short>();
        Variant::registerConverter<ValueType, unsigned short>();
        Variant::registerConverter<ValueType, int>();
        Variant::registerConverter<ValueType, unsigned int>();
        Variant::registerConverter<ValueType, long>();
        Variant::registerConverter<ValueType, unsigned long>();
        Variant::registerConverter<ValueType, long long>();
        Variant::registerConverter<ValueType, unsigned long long>();

        Variant::registerConverter<ValueType, float>();
        Variant::registerConverter<ValueType, double>();
        Variant::registerConverter<ValueType, long double>();

        Variant::registerConverter<ValueType, std::string>(util::toString<ValueType>);
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
        Variant::registerConverter<ValueType, bool>(toBool);

        Variant::registerConverter<ValueType, char>();
        Variant::registerConverter<ValueType, unsigned char>();
        Variant::registerConverter<ValueType, short>();
        Variant::registerConverter<ValueType, unsigned short>();
        Variant::registerConverter<ValueType, int>();
        Variant::registerConverter<ValueType, unsigned int>();
        Variant::registerConverter<ValueType, long>();
        Variant::registerConverter<ValueType, unsigned long>();
        Variant::registerConverter<ValueType, long long>();
        Variant::registerConverter<ValueType, unsigned long long>();

        Variant::registerConverter<ValueType, float>();
        Variant::registerConverter<ValueType, double>();
        Variant::registerConverter<ValueType, long double>();

        Variant::registerConverter<ValueType, std::string>(util::toString<ValueType>);
    }

    static bool toBool(const ValueType & value)
    {
        return value != 0;
    }
};

template <typename Enum>
struct VariantConverterInit<Enum, EnableIf<std::is_enum<Enum>>>
{
    void operator()()
    {
        Variant::registerConverter<Enum, std::string>(
            [](const Enum & value) -> std::string
                {
                    return EnumDefaultStrings<Enum>()().at(value);
                }
        );
    }
};

template <>
struct VariantConverterInit<Color>
{
    void operator()()
    {
        Variant::registerConverter<Color, std::string>(
            [](const Color & color) -> std::string
                {
                    return color.toString();
                }
        );
    }
};

template <>
struct VariantConverterInit<FilePath>
{
    void operator()()
    {
        Variant::registerConverter<FilePath, std::string>(
            [](const FilePath & path) -> std::string
                {
                    std::string str(path.toString());
                    return str;
                }
        );
    }
};

template <>
struct VariantConverterInit<std::string>
{
    void operator()()
    {
        Variant::registerConverter<std::string, bool>(toBool);

        Variant::registerConverter<std::string, char>(util::fromString<char>);
        Variant::registerConverter<std::string, unsigned char>(util::fromString<unsigned char>);
        Variant::registerConverter<std::string, short>(util::fromString<short>);
        Variant::registerConverter<std::string, unsigned short>(util::fromString<unsigned short>);
        Variant::registerConverter<std::string, int>(util::fromString<int>);
        Variant::registerConverter<std::string, unsigned int>(util::fromString<unsigned int>);
        Variant::registerConverter<std::string, long>(util::fromString<long>);
        Variant::registerConverter<std::string, unsigned long>(util::fromString<unsigned long>);
        Variant::registerConverter<std::string, long long>(util::fromString<long long>);
        Variant::registerConverter<std::string, unsigned long long>(util::fromString<unsigned long long>);

        Variant::registerConverter<std::string, float>(util::fromString<float>);
        Variant::registerConverter<std::string, double>(util::fromString<double>);
        Variant::registerConverter<std::string, long double>(util::fromString<long double>);

        Variant::registerConverter<std::string, FilePath>(
            [](const std::string & str) -> FilePath
                {
                    return FilePath(str);
                }
        );
        Variant::registerConverter<std::string, Color>(
            [](const std::string & str) -> Color
                {
                    bool ok = true;
                    return Color::fromString(str, &ok);
                }
        );
    }

    static bool toBool(const std::string & string)
    {
        return !string.empty();
    }
};

template <typename T>
struct VariantConverterInit<std::vector<T>>
{
    void operator()()
    {
        Variant::registerConverter<std::vector<T>, std::string>(toString);
        Variant::registerConverter<std::vector<T>, VariantArray>(toVariantArray);

    }

    static std::string toString(const std::vector<T> & elements)
    {
        return Variant(toVariantArray(elements)).value<std::string>();
    }

    static VariantArray toVariantArray(const std::vector<T> & elements)
    {
        VariantArray array;
        for (T value : elements)
        {
            array.push_back(value);
        }
        return array;
    }
};

template <>
struct VariantConverterInit<VariantArray>
{
    void operator()()
    {
        Variant::registerConverter<VariantArray, std::string>(toString);
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
        Variant::registerConverter<VariantMap, std::string>(toString);
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
