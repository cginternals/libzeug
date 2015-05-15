#pragma once

#include <map>
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
class EnumProperty : public ValueProperty<Enum, EnumPropertyInterface>
{
public:
    EnumProperty();
    virtual ~EnumProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    virtual bool hasChoices() const;
    const std::vector<Enum> & choices() const;
    void setChoices(const std::vector<Enum> & choices);
    virtual std::vector<std::string> choicesStrings() const;

    virtual std::vector<std::string> strings() const;
    void setStrings(const std::map<Enum, std::string> & pairs);

private:
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;
    std::vector<Enum> m_choices;
};

} // namespace reflectionzeug

#include <reflectionzeug/EnumProperty.hpp>
