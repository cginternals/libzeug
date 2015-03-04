#pragma once

#include <reflectionzeug/reflectionzeug_api.h>

#include <sstream>

#include <glm/glm.hpp>

#include <reflectionzeug/Variant.h>
#include <reflectionzeug/regex_namespace.h>

namespace reflectionzeug
{

template <typename ValueType, typename = void>
struct GlmVariantConverterInit
{
    void operator()()
    {
    }
};

template <>
struct GlmVariantConverterInit<glm::vec2>
{
    void operator()()
    {
        Variant::registerConverter<glm::vec2, std::string>(toString);
    }

    static std::string toString(const glm::vec2 & vec)
    {
        std::stringstream stream;
        stream << "(" << vec.x << ", " << vec.y << ")";
        return stream.str();
    }
};

template <>
struct GlmVariantConverterInit<glm::ivec2>
{
    void operator()()
    {
        Variant::registerConverter<glm::ivec2, std::string>(toString);
    }

    static std::string toString(const glm::ivec2 & vec)
    {
        std::stringstream stream;
        stream << "(" << vec.x << ", " << vec.y << ")";
        return stream.str();
    }
};

template <>
struct GlmVariantConverterInit<glm::vec3>
{
    void operator()()
    {
        Variant::registerConverter<glm::vec3, std::string>(toString);
    }

    static std::string toString(const glm::vec3 & vec)
    {
        std::stringstream stream;
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return stream.str();
    }
};

template <>
struct GlmVariantConverterInit<glm::ivec3>
{
    void operator()()
    {
        Variant::registerConverter<glm::ivec3, std::string>(toString);
    }

    static std::string toString(const glm::ivec3 & vec)
    {
        std::stringstream stream;
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return stream.str();
    }
};

template <>
struct GlmVariantConverterInit<glm::vec4>
{
    void operator()()
    {
        Variant::registerConverter<glm::vec4, std::string>(toString);
    }

    static std::string toString(const glm::vec4 & vec)
    {
        std::stringstream stream;
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        return stream.str();
    }
};

template <>
struct GlmVariantConverterInit<glm::ivec4>
{
    void operator()()
    {
        Variant::registerConverter<glm::ivec4, std::string>(toString);
    }

    static std::string toString(const glm::ivec4 & vec)
    {
        std::stringstream stream;
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        return stream.str();
    }
};

template <>
struct GlmVariantConverterInit<std::string>
{
    void operator()()
    {
        static const std::string r_ulonglong = "(?:0|[1-9]\\d*)";
        static const std::string r_longlong = "-?" + r_ulonglong;
        static const std::string r_number = r_longlong + "(?:\\.\\d+)?";

        static const regex_namespace::regex vec2Regex(
                "^\"\\( ?(" + r_number + "), (" + r_number + ") ?\\)\"$");
        Variant::registerConverter<std::string, glm::vec2>(
            [](const std::string & str) -> glm::vec2
                {
                    regex_namespace::smatch match;
                    regex_namespace::regex_match(str, match, vec2Regex);
                    return glm::vec2(util::fromString<double>(match[1]), util::fromString<double>(match[2]));
                }
        );

        static const regex_namespace::regex ivec2Regex(
                "^\"\\( ?(" + r_longlong + "), (" + r_longlong + ") ?\\)\"$");
        Variant::registerConverter<std::string, glm::ivec2>(
            [](const std::string & str) -> glm::ivec2
                {
                    regex_namespace::smatch match;
                    regex_namespace::regex_match(str, match, ivec2Regex);
                    return glm::ivec2(util::fromString<int>(match[1]), util::fromString<int>(match[2]));
                }
        );

        static const regex_namespace::regex vec3Regex(
                "^\"\\( ?(" + r_number + "), (" + r_number + "), (" + r_number + ") ?\\)\"$");
        Variant::registerConverter<std::string, glm::vec3>(
            [](const std::string & str) -> glm::vec3
                {
                    regex_namespace::smatch match;
                    regex_namespace::regex_match(str, match, vec3Regex);
                    return glm::vec3(util::fromString<double>(match[1]),
                            util::fromString<double>(match[2]),
                            util::fromString<double>(match[3]));
                }
        );

        static const regex_namespace::regex ivec3Regex(
                "^\"\\( ?(" + r_longlong + "), (" + r_longlong + "), (" + r_longlong + ") ?\\)\"$");
        Variant::registerConverter<std::string, glm::ivec3>(
            [](const std::string & str) -> glm::ivec3
                {
                    regex_namespace::smatch match;
                    regex_namespace::regex_match(str, match, ivec3Regex);
                    return glm::ivec3(util::fromString<int>(match[1]),
                            util::fromString<int>(match[2]),
                            util::fromString<int>(match[3]));
                }
        );

        static const regex_namespace::regex vec4Regex(
                "^\"\\( ?(" + r_number + "), (" + r_number + "), (" + r_number + "), (" + r_number + ") ?\\)\"$");
        Variant::registerConverter<std::string, glm::vec4>(
            [](const std::string & str) -> glm::vec4
                {
                    regex_namespace::smatch match;
                    regex_namespace::regex_match(str, match, vec4Regex);
                    return glm::vec4(util::fromString<double>(match[1]),
                            util::fromString<double>(match[2]),
                            util::fromString<double>(match[3]),
                            util::fromString<double>(match[4]));
                }
        );

        static const regex_namespace::regex ivec4Regex(
                "^\"\\( ?(" + r_longlong + "), (" + r_longlong + "), (" + r_longlong + "), (" + r_longlong + ") ?\\)\"$");
        Variant::registerConverter<std::string, glm::ivec4>(
            [](const std::string & str) -> glm::ivec4
                {
                    regex_namespace::smatch match;
                    regex_namespace::regex_match(str, match, ivec4Regex);
                    return glm::ivec4(util::fromString<int>(match[1]),
                            util::fromString<int>(match[2]),
                            util::fromString<int>(match[3]),
                            util::fromString<int>(match[4]));
                }
        );
    }
};

void initializeGlmVariantConverters()
{
    GlmVariantConverterInit<glm::vec2>()();
    GlmVariantConverterInit<glm::ivec2>()();
    GlmVariantConverterInit<glm::vec3>()();
    GlmVariantConverterInit<glm::ivec3>()();
    GlmVariantConverterInit<glm::vec4>()();
    GlmVariantConverterInit<glm::ivec4>()();

    GlmVariantConverterInit<std::string>()();
}

} // namespace reflectionzeug
