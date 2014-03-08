
#pragma once

#include <reflectionzeug/Property.h>
#include <reflectionzeug/EnumProperty.h>

enum class NormalMode : char { Vertex, LookAt, Custom };

namespace reflectionzeug
{

template <>
class Property<NormalMode> : public EnumProperty<NormalMode>
{
public:
    Property(const std::string & name, const NormalMode & value)
    :   EnumProperty<NormalMode>(name, value) {}

    Property(const std::string & name,
             const std::function<NormalMode ()> & getter,
             const std::function<void(const NormalMode &)> & setter)
    :   EnumProperty<NormalMode>(name, getter, setter) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, const NormalMode & (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const NormalMode &))
    :   EnumProperty<NormalMode>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, NormalMode (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(const NormalMode &))
    :   EnumProperty<NormalMode>(name, object, getter_pointer, setter_pointer) {}

    template <class Object>
    Property(const std::string & name,
             Object & object, NormalMode (Object::*getter_pointer)() const,
             void (Object::*setter_pointer)(NormalMode))
    :   EnumProperty<NormalMode>(name, object, getter_pointer, setter_pointer) {}

protected:
    virtual std::vector<std::pair<NormalMode, std::string>> pairs() const
    {
        return {
            { NormalMode::Vertex, "Vertex" },
            { NormalMode::LookAt, "LookAt" },
            { NormalMode::Custom, "Custom" }
        };
    }

};

} // namespace reflectionzeug
