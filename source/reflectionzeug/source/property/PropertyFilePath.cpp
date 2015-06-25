
#include <reflectionzeug/property/PropertyFilePath.h>

#include <iostream>

#include <reflectionzeug/property/AbstractVisitor.h>
#include <reflectionzeug/variant/Variant.h>


namespace reflectionzeug
{


PropertyFilePath::~PropertyFilePath()
{
}

std::string PropertyFilePath::toString() const
{
    return this->value().toString();
}

bool PropertyFilePath::fromString(const std::string & string)
{
    bool ok;
    FilePath value = FilePath::fromString(string, &ok);

    if (!ok)
    {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }

    this->setValue(value);
    return true;
}

Variant PropertyFilePath::toVariant() const
{
    // Return string variant
    return Variant(this->value().toString());
}

bool PropertyFilePath::fromVariant(const Variant & value)
{
    // Read from variant of the exact type
    if (value.hasType<FilePath>() || value.canConvert<FilePath>()) {
        setValue( value.value<FilePath>() );
        return true;
    }

    // Read from string
    else if (value.hasType<std::string>() || value.canConvert<std::string>()) {
        fromString( value.value<std::string>() );
        return true;
    }

    // Invalid value
    return false;
}

void PropertyFilePath::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyFilePath>(this);
}


} // namespace reflectionzeug
