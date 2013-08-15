
#include <assert.h>
#include <propertyzeug/Color.h>

namespace propertyzeug {

Color::Color()
:   m_rgba{.v=0}
{
}

Color::Color(const Color & color)
:   m_rgba{.v=color.rgba()}
{
}

Color::Color(unsigned int rgba)
:   m_rgba{.v=rgba}
{
}

Color::Color(int red, int green, int blue, int alpha)
:   m_rgba {
        .a=static_cast<char>(alpha),
        .r=static_cast<char>(red),
        .g=static_cast<char>(green),
        .b=static_cast<char>(blue)
    }
{
}

Color::~Color()
{
}

int Color::red() const
{
    return m_rgba.r;
}

void Color::setRed(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.r = static_cast<char>(value);
}

int Color::green() const
{
    return m_rgba.g;
}

void Color::setGreen(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.g = static_cast<char>(value);
}

int Color::blue() const
{
    return m_rgba.b;
}

void Color::setBlue(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.b = static_cast<char>(value);
}

int Color::alpha() const
{
    return m_rgba.a;
}

void Color::setAlpha(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.a = static_cast<char>(value);
}

unsigned int Color::rgba() const
{
    return m_rgba.v;
}

void Color::setRgba(unsigned int rgba)
{
    m_rgba.v = rgba;
}
    
} // namespace

