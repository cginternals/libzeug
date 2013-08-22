
#include <regex>
#include <propertyzeug/PropertyGroup.h>
#include <propertyzeug/AbstractPropertyVisitor.h>

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

void PropertyGroup::accept(AbstractPropertyVisitor & visitor)
{
    visitor.visit(*this);
}

bool PropertyGroup::addProperty(AbstractProperty * property)
{
    if (this->propertyExists(property->name()))
        return false;
    
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));
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
    assert(this->propertyExists(name));
    return *(this->property(name).to<PropertyGroup>());
}

const PropertyGroup & PropertyGroup::subGroup(const std::string & path) const
{
    assert(this->propertyExists(path));
    return *(this->property(path).to<PropertyGroup>());
}

bool PropertyGroup::propertyExists(const std::string & path) const
{
    if (std::regex_match(path, std::regex(AbstractProperty::s_nameRegexString)))
        return !(m_propertiesMap.find(path) == m_propertiesMap.end());
    
    static const std::regex pathRegex(AbstractProperty::s_nameRegexString +
                                      "(\\/" +
                                      AbstractProperty::s_nameRegexString +
                                      ")*");

    if (std::regex_match(path, pathRegex)) {
        std::smatch match;
        std::regex_search(path, match, std::regex("\\/"));
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

AbstractProperty * PropertyGroup::replaceProperty(const std::string & name, AbstractProperty * property)
{
    if (!this->directChildPropertyExists(name))
        return nullptr;
    
    this->insertPropertyAfter(name, property);
    return this->obtainProperty(name);
}

bool PropertyGroup::insertPropertyAfter(const std::string & name, AbstractProperty * property)
{
    if (!this->directChildPropertyExists(name) || this->directChildPropertyExists(property->name()))
        return false;
    
    auto propertyIterator = m_properties.begin();
    while (name == (*(propertyIterator++))->name());
    
    m_properties.insert(propertyIterator, property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));
    return true;
}

bool PropertyGroup::removeProperty(AbstractProperty * property)
{
    if (!this->directChildPropertyExists(property->name()))
        return false;
    
    m_properties.remove(property);
    m_propertiesMap.erase(property->name());
    return true;
}

AbstractProperty * PropertyGroup::obtainProperty(const std::string & name)
{
    if (!this->directChildPropertyExists(name))
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
            functor(*property->to<PropertyGroup>());
    }
}
    
} // namespace