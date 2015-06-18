
#include <reflectionzeug/base/Color.h>

#include <cassert>
#include <sstream>
#include <iomanip>

#include <reflectionzeug/base/util.h>


namespace reflectionzeug
{


Color Color::fromString(const std::string & string, bool * ok)
{
    *ok = util::matchesRegex(string, "#([0-9A-Fa-f]{8}|[0-9A-Fa-f]{6})");

    if (!*ok)
        return Color{};

    auto hexString = string.substr(1, string.length());

    if (hexString.size() == 6)
        hexString = "FF" + hexString;

    auto rgba = 0u;

    std::stringstream stream{hexString};
    stream >> std::hex;
    stream >> rgba;

    return Color{rgba};
}

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

std::string Color::asHex(bool alpha) const
{
    std::stringstream stream{};
    stream << "#";
    stream << std::hex << std::uppercase;

    if (alpha)
        stream << std::setw(2) << std::setfill('0') << this->alpha();

    stream << std::setw(2) << std::setfill('0') << red();
    stream << std::setw(2) << std::setfill('0') << green();
    stream << std::setw(2) << std::setfill('0') << blue();

    return stream.str();
}

std::string Color::toString() const
{
    return asHex(true);
}

std::string Color::toString(bool alpha) const
{
    return asHex(alpha);
}

bool Color::operator==(const Color & rhs) const
{
    return m_v == rhs.m_v;
}

bool Color::operator!=(const Color & rhs) const
{
    return !(*this == rhs);
}


} // namespace reflectionzeug
