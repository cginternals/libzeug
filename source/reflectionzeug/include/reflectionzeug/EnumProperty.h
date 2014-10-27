#pragma once

#include <utility>
#include <map>
#include <type_traits>
#include <vector>


#include <reflectionzeug/EnumPropertyInterface.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief Provides a property implementation for any kind of enum or enum class.
 *
 * Be sure to either specialize the EnumDefaultStrings template or explicitly
 * call setStrings() before using template instantiations.
 *
 * \ingroup property_hierarchy
 */
template <typename Enum>
class EnumProperty : public EnumPropertyInterface, public ValueProperty<Enum>
{
public:
    using Trait = std::is_enum<Enum>;
    
public:
    template <typename... Arguments>
    EnumProperty(Arguments&&... args);

    virtual ~EnumProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);
    
    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    void setStrings(const std::map<Enum, std::string> & pairs);
    
private:
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;
};

/**
 * \brief Specialize this template to provide default string mapping for an enum.
 */
template <typename Enum>
struct EnumDefaultStrings
{
    std::map<Enum, std::string> operator()()
    {
        return std::map<Enum, std::string>();
    }
};

} // namespace reflectionzeug

#include <reflectionzeug/EnumProperty.hpp>
