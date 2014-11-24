#include <reflectionzeug/Color.h>

#include <cassert>
#include <sstream>
#include <iomanip>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

Color Color::fromString(const std::string & string, bool * ok)
{
    *ok = util::matchesRegex(string, "#([0-9A-Fa-f]{8}|[0-9A-Fa-f]{6})");
    
    if (!(*ok))
        return Color();
        
    auto hexString = string.substr(1, string.length());
    
    if (hexString.size() == 6)
        hexString = "FF" + hexString;

    std::stringstream stream(hexString);
    unsigned int colorHex;
    stream >> std::hex >> std::uppercase;
    stream >> colorHex;

    return Color(colorHex);
}

Color::Color()
{
	v = 0;
}

Color::Color(const Color & color)
{
	v = color.rgba();
}

Color::Color(unsigned int rgba)
{
    v = rgba;
}

Color::Color(int red, int green, int blue, int alpha)
{
    m_rgba.a = static_cast<unsigned char>(alpha);
    m_rgba.r = static_cast<unsigned char>(red);
    m_rgba.g = static_cast<unsigned char>(green);
    m_rgba.b = static_cast<unsigned char>(blue);
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
    return v;
}

void Color::setRgba(unsigned int rgba)
{
    v = rgba;
}

std::string Color::asHex(bool alpha) const
{
    std::stringstream stream;
    stream << "#";
    stream << std::hex << std::uppercase << std::setw(2) << std::setfill('0');

    if (alpha)
        stream << rgba();
    else
        stream << red() << green() << blue();
    
    return stream.str();
}

std::string Color::toString(bool alpha) const
{
    return asHex(alpha);
}

} // namespace reflectionzeug
