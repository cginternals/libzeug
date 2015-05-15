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

void registerStringToGlmConverters();

template <>
struct GlmVariantConverterInit<std::string>
{
    void operator()()
    {
        registerStringToGlmConverters();
    }
};

void initializeGlmVariantConverters();



} // namespace reflectionzeug
