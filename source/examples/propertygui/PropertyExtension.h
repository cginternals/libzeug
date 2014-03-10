
#pragma once

#include <Qt>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/EnumProperty.h>
#include <reflectionzeug/ClassProperty.h>

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
class Property<Qt::CursorShape> : public EnumProperty<Qt::CursorShape>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) : 
        ValuePropertyInterface(name),
        EnumProperty<Qt::CursorShape>(name, std::forward<Args>(args)...) {}
    
protected:
    virtual std::vector<std::pair<Qt::CursorShape, std::string>> pairs() const
    {
        return {
            { Qt::PointingHandCursor, "Pointing Hand Cursor" },
            { Qt::BusyCursor, "Busy Cursor" },
            { Qt::ArrowCursor, "Arrow Cursor" },
            { Qt::WaitCursor, "Wait Cursor" }
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
