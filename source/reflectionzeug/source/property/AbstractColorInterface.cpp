
#include <reflectionzeug/property/AbstractColorInterface.h>

#include <sstream>
#include <iomanip>

#include <stringzeug/regex.h>


namespace reflectionzeug
{


AbstractColorInterface::AbstractColorInterface()
{
}

AbstractColorInterface::~AbstractColorInterface()
{
}

std::string AbstractColorInterface::toHexString(bool includeAlpha) const
{
    std::stringstream stream;
    stream << "#";
    stream << std::hex << std::uppercase;

    if (includeAlpha) {
        stream << std::setw(2) << std::setfill('0') << alpha();
    }

    stream << std::setw(2) << std::setfill('0') << red();
    stream << std::setw(2) << std::setfill('0') << green();
    stream << std::setw(2) << std::setfill('0') << blue();

    return stream.str();
}

bool AbstractColorInterface::fromHexString(const std::string & hex)
{
    // Check string format
    bool ok = stringzeug::matchesRegex(hex, "#([0-9A-Fa-f]{8}|[0-9A-Fa-f]{6})");
    if (!ok) {
        return false;
    }

    // Get ARGB color
    auto hexString = hex.substr(1, hex.length());
    if (hexString.size() == 6) {
        hexString = "FF" + hexString;
    }

    // Convert into ARGB integer value
    auto argb = 0u;
    std::stringstream stream{hexString};
    stream >> std::hex;
    stream >> argb;

    // Set color
    setBlue(argb & 0xff);
    argb = argb >> 8;
    setGreen(argb & 0xff);
    argb = argb >> 8;
    setRed(argb & 0xff);
    argb = argb >> 8;
    setAlpha(argb & 0xff);
    return true;
}

Variant AbstractColorInterface::toColorVariant() const
{
    // Return color as variant object
    Variant obj = Variant::map();
    (*(obj.asMap()))["r"] = red();
    (*(obj.asMap()))["g"] = green();
    (*(obj.asMap()))["b"] = blue();
    (*(obj.asMap()))["a"] = alpha();
    return obj;
}

bool AbstractColorInterface::fromColorVariant(const Variant & value)
{
    // Read from string
    if (value.hasType<std::string>() || value.canConvert<std::string>()) {
        fromHexString( value.value<std::string>() );
        return true;
    }

    // Read from object
    else if (value.hasType<VariantMap>()) {
        const VariantMap & map = *(value.asMap());
        int r = map.count("r") >= 1 ? map.at("r").value<int>() : 0;
        int g = map.count("g") >= 1 ? map.at("g").value<int>() : 0;
        int b = map.count("b") >= 1 ? map.at("b").value<int>() : 0;
        int a = map.count("a") >= 1 ? map.at("a").value<int>() : 255;
        setRGBA(r, g, b, a);
        return true;
    }

    return false;
}


} // namespace reflectionzeug
