
#pragma once

#include <reflectionzeug/Property.h>
#include <reflectionzeug/EnumProperty.h>
#include <reflectionzeug/ClassProperty.h>

enum class NormalMode : char { Vertex, LookAt, Custom };

class Switch
{
public:
    static Switch fromString(const std::string & string, bool * ok)
    {
        if (string == "On")
        {
            *ok = true;
            return Switch(true);
        }
        else if (string == "Off")
        {
            *ok = true;
            return Switch(false);
        }
        else
        {
            *ok = false;
            return Switch(false);
        }
    }

public:
    Switch(bool isOn) : m_isOn(isOn) {}

    std::string toString()
    {
        return m_isOn ? "On" : "Off";
    }

private:
    bool m_isOn;

};

namespace reflectionzeug
{

template <>
class Property<NormalMode> : public EnumProperty<NormalMode>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        EnumProperty<NormalMode>(name, std::forward<Args>(args)...) {}
    
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

template <>
class Property<Switch> : public ClassProperty<Switch>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        ClassProperty<Switch>(name, std::forward<Args>(args)...) {}

};

} // namespace reflectionzeug
