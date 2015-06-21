
#include <reflectionzeug/property/PropertyColor.h>

#include <iostream>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyColor::~PropertyColor()
{
}

Color PropertyColor::toColor() const
{
    return this->value();
}

bool PropertyColor::fromColor(const Color & color)
{
    this->setValue(color);
    return true;
}

std::string PropertyColor::toString() const
{
    return this->value().toString();
}

bool PropertyColor::fromString(const std::string & string)
{
    bool ok;
    Color value = Color::fromString(string, &ok);

    if (!ok)
    {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }

    this->setValue(value);
    return true;
}

Variant PropertyColor::toVariant() const
{
    // Get color
    Color color = this->value();

    // Return color as variant object
    Variant obj = Variant::map();
    (*(obj.toMap()))["r"] = color.red();
    (*(obj.toMap()))["g"] = color.green();
    (*(obj.toMap()))["b"] = color.blue();
    (*(obj.toMap()))["a"] = color.alpha();
    return obj;
}

bool PropertyColor::fromVariant(const Variant & value)
{
    // Read from variant of the exact type
    if (value.hasType<Color>() || value.canConvert<Color>()) {
        setValue( value.value<Color>() );
        return true;
    }

    // Read from string
    else if (value.hasType<std::string>() || value.canConvert<std::string>()) {
        fromString( value.value<std::string>() );
        return true;
    }

    // Read from object
    else if (value.hasType<VariantMap>()) {
        const VariantMap & map = *(value.toMap());
        int r = map.count("r") >= 1 ? map.at("r").value<int>() : 0;
        int g = map.count("g") >= 1 ? map.at("g").value<int>() : 0;
        int b = map.count("b") >= 1 ? map.at("b").value<int>() : 0;
        int a = map.count("a") >= 1 ? map.at("a").value<int>() : 255;
        this->setValue(Color(r, g, b, a));
        return true;
    }

    // Invalid value
    return false;
}

void PropertyColor::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyColor>(this);
    visitor->callVisitor<AbstractColorInterface>(this);
}


} // namespace reflectionzeug
