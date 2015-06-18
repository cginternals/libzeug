
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

void PropertyColor::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyColor>(this);
    visitor->callVisitor<AbstractColorInterface>(this);
}


} // namespace reflectionzeug
