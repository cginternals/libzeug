#pragma once

#include <string>

#include <reflectionzeug/reflectionzeug.h>


namespace reflectionzeug
{
    
/** \brief A simple RGBA color class for use as a property value.
 */
class REFLECTIONZEUG_API Color
{
public:
    Color();
    Color(const Color & color);
    explicit Color(unsigned int rgba);
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
    
    std::string asHex() const;
    
protected:
    union {
        struct {
            unsigned char b;
            unsigned char g;
            unsigned char r;
            unsigned char a;
        } m_rgba;
        unsigned int v;
    };
};

} // namespace reflectionzeug
