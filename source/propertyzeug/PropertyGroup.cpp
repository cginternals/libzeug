
#include <propertyzeug/PropertyGroup.h>

namespace propertyzeug {
    
PropertyGroup::PropertyGroup(std::string name, std::string title)
:   AbstractProperty(name, title)
{
}

PropertyGroup::~PropertyGroup()
{
    // TODO delete all properties?
}
    
bool PropertyGroup::isGroup() const
{
    return true;
}

bool PropertyGroup::addProperty(AbstractProperty * property)
{
    if (this->propertyExists(property->name()))
        return false;
    
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));
    return true;
}

AbstractProperty & PropertyGroup::property(const std::string & name)
{
    assert(this->propertyExists(name));
    return *m_propertiesMap.at(name);
}
    
const AbstractProperty & PropertyGroup::property(const std::string & name) const
{
    assert(this->propertyExists(name));
    return *m_propertiesMap.at(name);
}

bool PropertyGroup::propertyExists(const std::string & name) const
{
    if (m_propertiesMap.find(name) == m_propertiesMap.end())
        return false;
    else
        return true;
}

AbstractProperty * PropertyGroup::replaceProperty(const std::string & name, AbstractProperty * property)
{
    if (!this->propertyExists(name))
        return nullptr;
    
    this->insertPropertyAfter(name, property);
    return this->obtainProperty(name);
}

bool PropertyGroup::insertPropertyAfter(const std::string & name, AbstractProperty * property)
{
    if (!this->propertyExists(name) || this->propertyExists(property->name()))
        return false;
    
    auto propertyIterator = m_properties.begin();
    while (name == (*(propertyIterator++))->name());
    
    m_properties.insert(propertyIterator, property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));
    return true;
}

bool PropertyGroup::removeProperty(AbstractProperty * property)
{
    if (!this->propertyExists(property->name()))
        return false;
    
    m_properties.remove(property);
    m_propertiesMap.erase(property->name());
    return true;
}

AbstractProperty * PropertyGroup::obtainProperty(const std::string & name)
{
    if (!this->propertyExists(name))
        return nullptr;
    
    AbstractProperty * property = m_propertiesMap.find(name)->second;
    m_properties.remove(property);
    m_propertiesMap.erase(property->name());
    return property;
}

void PropertyGroup::forEachProperty(const std::function<void(AbstractProperty &)> functor)
{
    for (AbstractProperty * property : m_properties)
        functor(*property);
}

void PropertyGroup::forEachValueProperty(const std::function<void(AbstractProperty &)> functor)
{
    for (AbstractProperty * property : m_properties) {
        if (!property->isGroup())
            functor(*property);
    }
}

void PropertyGroup::forEachSubGroup(const std::function<void(PropertyGroup &)> functor)
{
    for (AbstractProperty * property : m_properties) {
        if (property->isGroup())
            functor(*static_cast<PropertyGroup *>(property));
    }
}
    
} // namespace