
#include <propertyzeug/PropertyGroup.h>

#include <regex>
#include <algorithm>

#include <propertyzeug/AbstractPropertyVisitor.h>

namespace zeug {
    
PropertyGroup::PropertyGroup(const std::string & name)
:   AbstractProperty(name)
{
}

PropertyGroup::~PropertyGroup()
{
    for (AbstractProperty * property : m_properties)
        delete property;
}
    
bool PropertyGroup::isGroup() const
{
    return true;
}

bool PropertyGroup::addProperty(AbstractProperty * property)
{
    if (this->property(property->name()) || property->hasParent())
        return false;
    
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));
    property->setParent(this);
    return true;
}
    
PropertyGroup * PropertyGroup::addGroup(const std::string & name)
{
    PropertyGroup * group = new PropertyGroup(name);
    
    if (!this->addProperty(group)) {
        delete group;
        return nullptr;
    }
    
    return group;
}

AbstractProperty * PropertyGroup::property(const std::string & path)
{
    static const std::regex pathRegex(AbstractProperty::s_nameRegexString +
                                      "(\\/" +
                                      AbstractProperty::s_nameRegexString +
                                      ")*");
    
    if (std::regex_match(path, pathRegex))
        return this->findProperty(path);
    else
        return nullptr;
}
    
const AbstractProperty * PropertyGroup::property(const std::string & path) const
{
    static const std::regex pathRegex(AbstractProperty::s_nameRegexString +
                                      "(\\/" +
                                      AbstractProperty::s_nameRegexString +
                                      ")*");
    
    if (std::regex_match(path, pathRegex))
        return this->findProperty(path);
    else
        return nullptr;
}

AbstractProperty * PropertyGroup::findProperty(const std::string & path)
{
    if (std::regex_match(path, std::regex(AbstractProperty::s_nameRegexString)))
        return this->propertyExists(path) ? m_propertiesMap.at(path) : nullptr;
    
    
    std::smatch match;
    std::regex_search(path, match, std::regex("\\/"));
    PropertyGroup * group = m_propertiesMap.at(match.prefix())->as<PropertyGroup>();
    return group ? group->property(match.suffix()) : nullptr;
}
    
const AbstractProperty * PropertyGroup::findProperty(const std::string & path) const
{
    if (std::regex_match(path, std::regex(AbstractProperty::s_nameRegexString)))
        return this->propertyExists(path) ? m_propertiesMap.at(path) : nullptr;
    
    std::smatch match;
    std::regex_search(path, match, std::regex("\\/"));
    PropertyGroup * group = m_propertiesMap.at(match.prefix())->as<PropertyGroup>();
    return group ? group->property(match.suffix()) : nullptr;
}

PropertyGroup * PropertyGroup::group(const std::string & path)
{
    return this->property(path)->as<PropertyGroup>();
}

const PropertyGroup * PropertyGroup::group(const std::string & path) const
{
    return this->property(path)->as<PropertyGroup>();
}
    
AbstractProperty * PropertyGroup::property(unsigned int index)
{
    return (index < this->propertyCount()) ? m_properties[index] : nullptr;
}

const AbstractProperty * PropertyGroup::property(unsigned int index) const
{
    if (index < this->propertyCount())
        return nullptr;
    return m_properties[index];
}

bool PropertyGroup::propertyExists(const std::string & name) const
{
    return !(m_propertiesMap.find(name) == m_propertiesMap.end());
}

bool PropertyGroup::groupExists(const std::string & name) const
{
    return this->propertyExists(name) && this->group(name);
}

bool PropertyGroup::removeProperty(AbstractProperty * property)
{
    if (!this->propertyExists(property->name()))
        return false;
    
    auto propertyIt = std::find(m_properties.begin(), m_properties.end(), property);
    m_properties.erase(propertyIt);
    m_propertiesMap.erase(property->name());
    return true;
}

AbstractProperty * PropertyGroup::obtainProperty(const std::string & name)
{
    if (!this->propertyExists(name))
        return nullptr;
    
    AbstractProperty * property = m_propertiesMap.find(name)->second;
    auto propertyIt = std::find(m_properties.begin(), m_properties.end(), property);
    m_properties.erase(propertyIt);
    m_propertiesMap.erase(property->name());
    property->removeParent();
    return property;
}

unsigned int PropertyGroup::propertyCount() const
{
    return m_properties.size();
}
    
int PropertyGroup::indexOfProperty(const std::string & name) const
{
    if (!this->propertyExists(name))
        return -1;

    AbstractProperty * property = m_propertiesMap.find(name)->second;
    return static_cast<int>(std::distance(
        m_properties.begin(), std::find(m_properties.begin(), m_properties.end(), property)));
}
    
bool PropertyGroup::hasProperties() const
{
    return this->propertyCount() != 0;
}

void PropertyGroup::forEachProperty(const std::function<void(AbstractProperty &)> functor)
{
    for (AbstractProperty * property : m_properties)
        functor(*property);
}

void PropertyGroup::forEachProperty(const std::function<void(AbstractProperty &)> functor) const
{
    for (AbstractProperty * property : m_properties)
        functor(*property);
}

void PropertyGroup::forEachValueProperty(const std::function<void(ValueProperty &)> functor)
{
    for (AbstractProperty * property : m_properties) {
        if (!property->isGroup())
            functor(*property->asValue());
    }
}

void PropertyGroup::forEachValueProperty(const std::function<void(ValueProperty &)> functor) const
{
    for (AbstractProperty * property : m_properties) {
        if (!property->isGroup())
            functor(*property->asValue());
    }
}

void PropertyGroup::forEachSubGroup(const std::function<void(PropertyGroup &)> functor)
{
    for (AbstractProperty * property : m_properties) {
        if (property->isGroup())
            functor(*property->as<PropertyGroup>());
    }
}

void PropertyGroup::forEachSubGroup(const std::function<void(PropertyGroup &)> functor) const
{
    for (AbstractProperty * property : m_properties) {
        if (property->isGroup())
            functor(*property->as<PropertyGroup>());
    }
}
    
} // namespace
