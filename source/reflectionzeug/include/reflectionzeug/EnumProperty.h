
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
    EnumProperty(const Enum & value);

    EnumProperty(const std::function<Enum()> & getter,
                 const std::function<void(const Enum &)> & setter);

    template <class Object>
    EnumProperty(Object & object, 
                 const Enum & (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Enum &));

    template <class Object>
    EnumProperty(Object & object, 
                 Enum (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Enum &));

    template <class Object>
    EnumProperty(Object & object, 
                 Enum (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(Enum));

    virtual ~EnumProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);
    
    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);
    
    virtual std::vector<std::string> strings() const;
    
    void setStrings(const std::vector<std::pair<Enum, std::string>> & pairs);

private:
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;

};

} // namespace reflectionzeug

#include "EnumProperty.hpp"
