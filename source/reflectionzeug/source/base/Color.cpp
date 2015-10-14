
#include <reflectionzeug/base/Color.h>

#include <cassert>

// #include <stringzeug/conversion.h>


namespace reflectionzeug
{


Color::Color()
: m_v{0u}
{
}

Color::Color(unsigned int rgba)
: m_v{rgba}
{
}

Color::Color(int red, int green, int blue, int alpha)
{
    m_rgba.a = static_cast<unsigned char>(alpha);
    m_rgba.r = static_cast<unsigned char>(red);
    m_rgba.g = static_cast<unsigned char>(green);
    m_rgba.b = static_cast<unsigned char>(blue);
}

bool Color::operator==(const Color & rhs) const
{
    return m_v == rhs.m_v;
}

bool Color::operator!=(const Color & rhs) const
{
    return !(*this == rhs);
}

int Color::red() const
{
    return m_rgba.r;
}

void Color::setRed(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.r = static_cast<unsigned char>(value);
}

int Color::green() const
{
    return m_rgba.g;
}

void Color::setGreen(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.g = static_cast<unsigned char>(value);
}

int Color::blue() const
{
    return m_rgba.b;
}

void Color::setBlue(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.b = static_cast<unsigned char>(value);
}

int Color::alpha() const
{
    return m_rgba.a;
}

void Color::setAlpha(int value)
{
    assert(0 <= value && value <= 255);
    m_rgba.a = static_cast<unsigned char>(value);
}

unsigned int Color::rgba() const
{
    return m_v;
}

void Color::setRgba(unsigned int rgba)
{
    m_v = rgba;
}


} // namespace reflectionzeug
