#pragma once

#include <reflectionzeug/Property.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <type_traits>

namespace {

template <typename T, unsigned Count>
std::string toString(const T * data)
{
    std::stringstream ss;

    ss << "(";

    for (unsigned i = 0; i < Count; ++i)
    {
        if (i > 0)
            ss << ", ";

        ss << data[i];
    }

    ss << ")";

    return ss.str();
}

template <typename T, unsigned Count>
bool fromString(const std::string & string, T * data)
{
    std::string elementRegex = std::is_integral<T>::value ? "(-|\\+)?\\d+" : "(-|\\+)?\\d+\\.?\\d*";

    std::stringstream ss;
    ss << "\\s*\\(";
    for (unsigned i=0; i<Count-1; ++i)
    {
        ss << "(" << elementRegex << ")";
        ss << "\\s*,\\s*";
    }
    ss << elementRegex << "\\)\\s*";

    if (!reflectionzeug::util::matchesRegex(string, ss.str()))
        return false;

    std::vector<std::string> parts = reflectionzeug::util::extract(string, elementRegex);

    assert(parts.size() == Count);

    for (unsigned i = 0; i < Count; ++i)
    {
        const std::string & part = parts[i];
        data[i] = std::is_integral<T>::value ? static_cast<T>(std::stoi(part)) : static_cast<T>(std::stod(part));
    }

    return true;
}

}

namespace reflectionzeug {

template <>
class Property<glm::vec2> : public ValueProperty<glm::vec2>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) :
        ValuePropertyInterface(name),
        ValueProperty<glm::vec2>(std::forward<Args>(args)...) {}

    virtual std::string toString() const override { return ::toString<glm::vec2::value_type, 2u>(glm::value_ptr(this->value())); }

    virtual bool fromString(const std::string & string) override
    {
        glm::vec2 value;
        if (!::fromString<glm::vec2::value_type, 2>(string, glm::value_ptr(value)))
            return false;

        setValue(value);
        return true;
    }
};

template <>
class Property<glm::ivec2> : public ValueProperty<glm::ivec2>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) :
        ValuePropertyInterface(name),
        ValueProperty<glm::ivec2>(std::forward<Args>(args)...) {}

    virtual std::string toString() const override { return ::toString<glm::ivec2::value_type, 2>(glm::value_ptr(value())); }

    virtual bool fromString(const std::string & string) override
    {
        glm::ivec2 value;
        if (!::fromString<glm::ivec2::value_type, 2>(string, glm::value_ptr(value)))
            return false;

        setValue(value);
        return true;
    }
};

template <>
class Property<glm::vec3> : public ValueProperty<glm::vec3>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) :
        ValuePropertyInterface(name),
        ValueProperty<glm::vec3>(std::forward<Args>(args)...) {}

    virtual std::string toString() const override { return ::toString<glm::vec3::value_type, 3>(glm::value_ptr(value())); }

    virtual bool fromString(const std::string & string) override
    {
        glm::vec3 value;
        if (!::fromString<glm::vec3::value_type, 3>(string, glm::value_ptr(value)))
            return false;

        setValue(value);
        return true;
    }
};

template <>
class Property<glm::vec4> : public ValueProperty<glm::vec4>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) :
        ValuePropertyInterface(name),
        ValueProperty<glm::vec4>(std::forward<Args>(args)...) {}

    virtual std::string toString() const override { return ::toString<glm::vec4::value_type, 4>(glm::value_ptr(value())); }

    virtual bool fromString(const std::string & string) override
    {
        glm::vec4 value;
        if (!::fromString<glm::vec4::value_type, 4>(string, glm::value_ptr(value)))
            return false;

        setValue(value);
        return true;
    }
};

}
