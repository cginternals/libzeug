
#pragma once

#include <string>

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
