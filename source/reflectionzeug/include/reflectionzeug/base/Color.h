
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


/**
*  @brief
*    A simple RGBA color class
*/
class REFLECTIONZEUG_API Color
{
public:
    Color();
    explicit Color(unsigned int rgba);
    Color(int red, int green, int blue, int alpha = 255);

    bool operator==(const Color & rhs) const;
    bool operator!=(const Color & rhs) const;

    unsigned int rgba() const;
    void setRgba(unsigned int rgba);

    int red() const;
    void setRed(int value);
    int green() const;
    void setGreen(int value);
    int blue() const;
    void setBlue(int value);
    int alpha() const;
    void setAlpha(int value);

    Color interpolate(const Color & other, float interpolationValue) const;

protected:
    union {
        struct {
            unsigned char b;
            unsigned char g;
            unsigned char r;
            unsigned char a;
        } m_rgba;
        unsigned int m_v;
    };
};


} // namespace reflectionzeug
