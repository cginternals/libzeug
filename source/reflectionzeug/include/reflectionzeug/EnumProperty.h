
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
    EnumProperty(const std::string & name, const Enum & value);

    EnumProperty(const std::string & name,
                 const std::function<Enum()> & getter,
                 const std::function<void(const Enum &)> & setter);

    template <class Object>
    EnumProperty(const std::string & name,
                 Object & object, const Enum & (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Enum &));

    template <class Object>
    EnumProperty(const std::string & name,
                 Object & object, Enum (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Enum &));

    template <class Object>
    EnumProperty(const std::string & name,
                 Object & object, Enum (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(Enum));

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

    virtual const std::vector<std::string> & stringList() const;

    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);

protected:
    virtual std::vector<std::pair<Enum, std::string>> pairs() const = 0;

private:
    void init() const;

private:
    std::vector<std::string> m_stringList;
    std::map<Enum, std::string> m_stringMap;
    std::map<std::string, Enum> m_enumMap;
    bool m_isInitialized;

};

} // namespace reflectionzeug

#include "EnumProperty.hpp"
