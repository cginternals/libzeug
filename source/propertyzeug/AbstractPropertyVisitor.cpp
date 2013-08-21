
#include <propertyzeug/AbstractPropertyVisitor.h>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/Property.h>

namespace propertyzeug {

AbstractPropertyVisitor::~AbstractPropertyVisitor()
{
}

void AbstractPropertyVisitor::traverse(PropertyGroup & group)
{
    group.forEachProperty([this](AbstractProperty & property) {
        property.accept(*this);
    });
}

} // namespace