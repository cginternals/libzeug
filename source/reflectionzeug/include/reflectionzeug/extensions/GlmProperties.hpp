
#pragma once


#include <sstream>
#include <type_traits>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <reflectionzeug/property/Property.h>


namespace reflectionzeug
{


/**
*  @brief
*    Convert glm vector into string
*
*  @param[in] data
*    Pointer to vector data
*
*  @return
*    String representation
*/
template <typename T, unsigned Size>
std::string glmToString(const T * data)
{
    std::stringstream ss;

    ss << "(";

    for (unsigned i = 0; i < Size; ++i)
    {
        if (i > 0)
            ss << ", ";

        ss << data[i];
    }

    ss << ")";

    return ss.str();
}

/**
*  @brief
*    Convert string into glm vector
*
*  @param[in] string
*    String representation
*  @param[in] data
*    Pointer to vector data
*
*  @return
*    'true' if all went fine, else 'false'
*/
template <typename T, unsigned Size>
bool glmFromString(const std::string & string, T * data)
{
    std::string elementRegex = std::is_integral<T>::value ? "(-|\\+)?\\d+" : "(-|\\+)?\\d+\\.?\\d*";

    std::stringstream ss;
    ss << "\\s*\\(";
    for (unsigned i=0; i<Size-1; ++i)
    {
        ss << "(" << elementRegex << ")";
        ss << "\\s*,\\s*";
    }
    ss << elementRegex << "\\)\\s*";

    if (!reflectionzeug::util::matchesRegex(string, ss.str()))
        return false;

    std::vector<std::string> parts = reflectionzeug::util::extract(string, elementRegex);

    assert(parts.size() == Size);

    for (unsigned i = 0; i < Size; ++i)
    {
        const std::string & part = parts[i];
        data[i] = std::is_integral<T>::value ? static_cast<T>(std::stoi(part)) : static_cast<T>(std::stod(part));
    }

    return true;
}

/**
*  @brief
*    Property implementation for GLM vector types
*/
template <typename VectorType, typename ValueType, unsigned Size>
class PropertyGlmVec : public reflectionzeug::AbstractValueProperty<VectorType>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Arguments>
    PropertyGlmVec(Arguments&&... args)
    : reflectionzeug::AbstractValueProperty<VectorType>(std::forward<Arguments>(args)...)
    {
    }

    // Virtual AbstractProperty interface
    virtual std::string toString() const override 
    {
        return glmToString<ValueType, Size>(glm::value_ptr(this->value())); 
    }

    virtual bool fromString(const std::string & string) override
    {
        VectorType value;
        if (!glmFromString<ValueType, Size>(string, glm::value_ptr(value)))
            return false;

        this->setValue(value);
        return true;
    }

    virtual Variant toVariant() const override
    {
        // Return variant array
        VectorType vector = this->value();
        Variant array = Variant::array();
        for (size_t i=0; i<Size; i++) {
            array.toArray()->push_back(vector[i]);
        }
        return array;
    }

    virtual bool fromVariant(const Variant & value) override
    {
        // Read from variant of the exact type
        if (value.hasType<VectorType>() || value.canConvert<VectorType>()) {
            this->setValue( value.value<VectorType>() );
            return true;
        }

        // Read from string
        else if (value.hasType<std::string>() || value.canConvert<std::string>()) {
            this->fromString( value.value<std::string>() );
            return true;
        }

        // Read from variant array
        else if (value.hasType<VariantArray>()) {
            const VariantArray & array = *(value.toArray());
            VectorType vector;
            for (size_t i=0; i<Size; i++) {
                vector[i] = array[i].value<ValueType>();
            }
            this->setValue(vector);
            return true;
        }

        // Invalid value
        return false;
    }
};

/**
*  @brief
*    Property selector for properties of type glm::vec2
*/
template <>
struct PropertyTypeSelector<glm::vec2>
{
    using Type = PropertyGlmVec<glm::vec2, glm::vec2::value_type, 2>;
};

/**
*  @brief
*    Property selector for properties of type glm::ivec2
*/
template <>
struct PropertyTypeSelector<glm::ivec2>
{
    using Type = PropertyGlmVec<glm::ivec2, glm::ivec2::value_type, 2>;
};

/**
*  @brief
*    Property selector for properties of type glm::vec3
*/
template <>
struct PropertyTypeSelector<glm::vec3>
{
    using Type = PropertyGlmVec<glm::vec3, glm::vec3::value_type, 3>;
};

/**
*  @brief
*    Property selector for properties of type glm::ivec3
*/
template <>
struct PropertyTypeSelector<glm::ivec3>
{
    using Type = PropertyGlmVec<glm::ivec3, glm::ivec3::value_type, 3>;
};

/**
*  @brief
*    Property selector for properties of type glm::ivec4
*/
template <>
struct PropertyTypeSelector<glm::vec4>
{
    using Type = PropertyGlmVec<glm::vec4, glm::vec4::value_type, 4>;
};

/**
*  @brief
*    Property selector for properties of type glm::ivec4
*/
template <>
struct PropertyTypeSelector<glm::ivec4>
{
    using Type = PropertyGlmVec<glm::ivec4, glm::ivec4::value_type, 4>;
};


} // namespace reflectionzeug
