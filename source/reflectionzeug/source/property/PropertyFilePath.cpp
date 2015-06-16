
#include <reflectionzeug/property/PropertyFilePath.h>

#include <iostream>

#include <reflectionzeug/property/AbstractVisitor.h>


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

void PropertyFilePath::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyFilePath>(this);
}


} // namespace reflectionzeug
