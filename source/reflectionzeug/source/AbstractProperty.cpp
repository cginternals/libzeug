#include <reflectionzeug/AbstractProperty.h>

#include <utility>

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/AbstractPropertyCollection.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

namespace reflectionzeug 
{
    
const std::string AbstractProperty::s_nameRegexString("[a-zA-Z_]+\\w*");

AbstractProperty::AbstractProperty()
{
}

AbstractProperty::AbstractProperty(const std::string & name)
{
    setName(name);
}

AbstractProperty::~AbstractProperty()
{
}

std::string AbstractProperty::name() const
{
    return option("name").value<std::string>();
}
    
bool AbstractProperty::setName(const std::string & name)
{    
    if (!util::matchesRegex(name, s_nameRegexString))
        return false;
    
    setOption("name", name);
    return true;
}
    
bool AbstractProperty::hasName() const
{
    return hasOption("name") && name().size() > 0;
}

bool AbstractProperty::hasOption(const std::string & key) const
{
    return m_options.count(key) != 0;
}

Variant AbstractProperty::option(const std::string & key) const
{
    if (!this->hasOption(key))
        return Variant();

    return m_options.at(key);
}

void AbstractProperty::setOption(const std::string & key, const Variant & value)
{
    m_options[key] = value;
}

bool AbstractProperty::removeOption(const std::string & key)
{
    if (!this->hasOption(key))
        return false;
        
    m_options.erase(key);
    return true;
}

void AbstractProperty::setOptions(const VariantMap & map)
{
    m_options.insert(map.begin(), map.end());
}

AbstractValueProperty * AbstractProperty::asValue()
{
    return dynamic_cast<AbstractValueProperty *>(this);
}

const AbstractValueProperty * AbstractProperty::asValue() const
{
    return dynamic_cast<const AbstractValueProperty *>(this);
}

AbstractPropertyCollection * AbstractProperty::asCollection()
{
    return dynamic_cast<AbstractPropertyCollection *>(this);
}

const AbstractPropertyCollection * AbstractProperty::asCollection() const
{
    return dynamic_cast<const AbstractPropertyCollection *>(this);
}

PropertyGroup * AbstractProperty::asGroup()
{
    return dynamic_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractProperty::asGroup() const
{
    return dynamic_cast<const PropertyGroup *>(this);
}
    
bool AbstractProperty::isCollection() const
{
    return false;
}

bool AbstractProperty::isValue() const
{
    return false;
}
    
bool AbstractProperty::isGroup() const
{
    return false;
}

} // namespace reflectionzeug
