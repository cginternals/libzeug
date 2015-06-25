
#include <reflectionzeug/property/PropertyColor.h>

#include <iostream>

#include <reflectionzeug/base/Color.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyColor::~PropertyColor()
{
}

void PropertyColor::getRGBA(int & r, int & g, int & b, int & a) const
{
    Color color = this->value();
    r = color.red();
    g = color.green();
    b = color.blue();
    a = color.alpha();
}

void PropertyColor::setRGBA(int r, int g, int b, int a)
{
    this->setValue(Color(r, g, b, a));
}

int PropertyColor::red() const
{
    return this->value().red();
}

void PropertyColor::setRed(int red)
{
    Color color = this->value();
    color.setRed(red);
    this->setValue(color);
}

int PropertyColor::green() const
{
    return this->value().green();
}

void PropertyColor::setGreen(int green)
{
    Color color = this->value();
    color.setGreen(green);
    this->setValue(color);
}

int PropertyColor::blue() const
{
    return this->value().blue();
}

void PropertyColor::setBlue(int blue)
{
    Color color = this->value();
    color.setBlue(blue);
    this->setValue(color);
}

int PropertyColor::alpha() const
{
    return this->value().alpha();
}

void PropertyColor::setAlpha(int alpha)
{
    Color color = this->value();
    color.setAlpha(alpha);
    this->setValue(color);
}

std::string PropertyColor::toString() const
{
    // Return hex representation
    return toHexString();
}

bool PropertyColor::fromString(const std::string & string)
{
    // Read from hex representation
    return fromHexString(string);
}

Variant PropertyColor::toVariant() const
{
    // Return color as variant object
    return toColorVariant();
}

bool PropertyColor::fromVariant(const Variant & value)
{
    // Read from variant of the exact type
    if (value.hasType<Color>() || value.canConvert<Color>()) {
        setValue( value.value<Color>() );
        return true;
    }

    // Read from string or object representation
    else {
        return fromColorVariant(value);
    }
}

void PropertyColor::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyColor>(this);
    visitor->callVisitor<AbstractColorInterface>(this);
}


} // namespace reflectionzeug
