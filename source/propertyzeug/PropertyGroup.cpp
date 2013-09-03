
#include <regex>
#include <algorithm>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/AbstractPropertyVisitor.h>

namespace propertyzeug {
    
PropertyGroup::PropertyGroup(const std::string & name)
:   AbstractProperty(name)
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

void PropertyGroup::accept(AbstractPropertyVisitor & visitor)
{
    visitor.visit(*this);
}

bool PropertyGroup::addProperty(AbstractProperty * property)
{
    if (this->propertyExists(property->name()) || property->hasParent())
        return false;
    
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));
    property->setParent(this);
    return true;
}

AbstractProperty & PropertyGroup::property(const std::string & path)
{
    assert(this->propertyExists(path));
    
    if (std::regex_match(path, std::regex(AbstractProperty::s_nameRegexString)))
        return *m_propertiesMap.at(path);
    
    std::smatch match;
    std::regex_search(path, match, std::regex("\\/"));
    return m_propertiesMap.at(match.prefix())->to<PropertyGroup>()->property(match.suffix());
}
    
const AbstractProperty & PropertyGroup::property(const std::string & path) const
{
    assert(this->propertyExists(path));
    
    if (std::regex_match(path, std::regex(AbstractProperty::s_nameRegexString)))
        return *m_propertiesMap.at(path);
    
    std::smatch match;
    std::regex_search(path, match, std::regex("\\/"));
    return m_propertiesMap.at(match.prefix())->to<PropertyGroup>()->property(match.suffix());
}

PropertyGroup & PropertyGroup::subGroup(const std::string & name)
{
    assert(this->subGroupExists(name));
    return *(this->property(name).to<PropertyGroup>());
}

const PropertyGroup & PropertyGroup::subGroup(const std::string & path) const
{
    assert(this->subGroupExists(path));
    return *(this->property(path).to<PropertyGroup>());
}
    
AbstractProperty & PropertyGroup::property(unsigned int index)
{
    assert(index < this->propertyCount());
    return *m_properties[index];
}

const AbstractProperty & PropertyGroup::property(unsigned int index) const
{
    assert(index < this->propertyCount());
    return *m_properties[index];
}

bool PropertyGroup::propertyExists(const std::string & path) const
{
    if (std::regex_match(path, std::regex(AbstractProperty::s_nameRegexString)))
        return this->directChildPropertyExists(path);
    
    static const std::regex pathRegex(AbstractProperty::s_nameRegexString +
                                      "(\\/" +
                                      AbstractProperty::s_nameRegexString +
                                      ")*");

    if (std::regex_match(path, pathRegex)) {
        std::smatch match;
        std::regex_search(path, match, std::regex("\\/"));
        if (this->directChildPropertyExists(match.prefix()))
            return m_propertiesMap.at(match.prefix())->to<PropertyGroup>()->propertyExists(match.suffix());
    }
    
    return false;
}
    
bool PropertyGroup::subGroupExists(const std::string & path) const
{
    return this->propertyExists(path) && this->property(path).isGroup();
}
    
bool PropertyGroup::directChildPropertyExists(const std::string & name) const
{
    return !(m_propertiesMap.find(name) == m_propertiesMap.end());
}
    
bool PropertyGroup::directChildSubGroupExists(const std::string & path) const
{
    return this->directChildPropertyExists(path) && this->property(path).isGroup();
}

bool PropertyGroup::removeProperty(AbstractProperty * property)
{
    if (!this->directChildPropertyExists(property->name()))
        return false;
    
    auto propertyIt = std::find(m_properties.begin(), m_properties.end(), property);
    m_properties.erase(propertyIt);
    m_propertiesMap.erase(property->name());
    return true;
}

AbstractProperty * PropertyGroup::obtainProperty(const std::string & name)
{
    if (!this->directChildPropertyExists(name))
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
    if (!this->directChildPropertyExists(name))
        return -1;
    
    AbstractProperty * property = m_propertiesMap.find(name)->second;
    return std::distance(m_properties.begin(),
                         std::find(m_properties.begin(),
                                   m_properties.end(), property));
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
            functor(*property->to<PropertyGroup>());
    }
}
    
} // namespace
