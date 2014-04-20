
#pragma once

#include <utility>
#include <map>
#include <vector>

#include <reflectionzeug/EnumPropertyInterface.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

template <typename Enum>
class EnumProperty : public EnumPropertyInterface, public ValueProperty<Enum>
{
public:
    template <typename... Arguments>
    EnumProperty(Arguments&&... args);

    virtual ~EnumProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);
    
    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
    
    const std::vector<Enum> & choices() const;
    void setChoices(const std::vector<Enum> & choices);
    virtual bool hasChoices() const;
    void clearChoices();
    
    virtual std::vector<std::string> stringChoices() const;
    virtual std::vector<std::string> strings() const;
    
    void setStrings(const std::map<Enum, std::string> & pairs);
    
private:
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;
    std::vector<Enum> m_choices;
};

template <typename Enum>
struct EnumDefaultStrings
{
    std::map<Enum, std::string> operator()()
    {
        return std::map<Enum, std::string>();
    }
};

} // namespace reflectionzeug

#include "EnumProperty.hpp"
