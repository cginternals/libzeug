
#pragma once

#include <propertyzeug/propertyzeug.h>

namespace propertyzeug {
    
/** @brief
 * A simple RGBA color class for use as a property value.
 */

class PROPERTYZEUG_API Color
{
public:
    Color();
    Color(const Color & color);
    Color(unsigned int rgba);
    Color(int red, int green, int blue, int alpha = 255);
    virtual ~Color();

    int red() const;
    void setRed(int value);
    int green() const;
    void setGreen(int value);
    int blue() const;
    void setBlue(int value);
    int alpha() const;
    void setAlpha(int value);
    
    unsigned int rgba() const;
    void setRgba(unsigned int rgba);
    
protected:
    union {
        struct {
            unsigned char a;
            unsigned char r;
            unsigned char g;
            unsigned char b;
        };
        unsigned int v;
    } m_rgba;
};

} // namespace