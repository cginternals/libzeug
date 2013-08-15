
#include <assert.h>
#include <propertyzeug/Color.h>

Color::Color()
:   m_argb{.v=0}
{
}

Color::Color(unsigned int argb)
:   m_argb{.v=argb}
{
}

Color::Color(int red, int green, int blue, int alpha)
:   m_argb {
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
    return m_argb.r;
}

void Color::setRed(int value)
{
    assert(0 <= value && value <= 255);
    m_argb.r = static_cast<char>(value);
}

int Color::green() const
{
    return m_argb.g;
}

void Color::setGreen(int value)
{
    assert(0 <= value && value <= 255);
    m_argb.g = static_cast<char>(value);
}

int Color::blue() const
{
    return m_argb.b;
}

void Color::setBlue(int value)
{
    assert(0 <= value && value <= 255);
    m_argb.b = static_cast<char>(value);
}

int Color::alpha() const
{
    return m_argb.a;
}

void Color::setAlpha(int value)
{
    assert(0 <= value && value <= 255);
    m_argb.a = static_cast<char>(value);
}

unsigned int Color::argb() const
{
    return m_argb.v;
}

void Color::setArgb(unsigned int argb)
{
    m_argb.v = argb;
}

