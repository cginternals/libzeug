
#include <reflectionzeug/property/AbstractProperty.h>
#include <reflectionzeug/property/AbstractCollection.h>
#include <reflectionzeug/property/PropertyGroup.h>


namespace reflectionzeug
{


AbstractProperty::AbstractProperty(const std::string & name)
: m_name(name)
{
}

AbstractProperty::~AbstractProperty()
{
}

std::string AbstractProperty::name() const
{
    return m_name;
}

bool AbstractProperty::hasName() const
{
    return !m_name.empty();
}

void AbstractProperty::accept(AbstractVisitor * visitor)
{
}

bool AbstractProperty::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractProperty::isGroup() const
{
    return (dynamic_cast<const PropertyGroup *>(this) != nullptr);
}

AbstractCollection * AbstractProperty::asCollection()
{
    return dynamic_cast<AbstractCollection *>(this);
}

const AbstractCollection * AbstractProperty::asCollection() const
{
    return dynamic_cast<const AbstractCollection *>(this);
}

PropertyGroup * AbstractProperty::asGroup()
{
    return dynamic_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractProperty::asGroup() const
{
    return dynamic_cast<const PropertyGroup *>(this);
}

const VariantMap & AbstractProperty::options() const
{
    return m_options;
}

Variant AbstractProperty::option(const std::string & key) const
{
    if (!this->hasOption(key))
        return Variant();

    return m_options.at(key);
}

bool AbstractProperty::hasOption(const std::string & key) const
{
    return m_options.count(key) != 0;
}

void AbstractProperty::setOption(const std::string & key, const Variant & value)
{
    m_options[key] = value;
    optionChanged(key);
}

void AbstractProperty::setOptions(const VariantMap & map)
{
    for (const auto & pair : map)
    {
        m_options[pair.first] = pair.second;
        optionChanged(pair.first);
    }
}

bool AbstractProperty::removeOption(const std::string & key)
{
    if (!this->hasOption(key))
        return false;

    m_options.erase(key);
    optionChanged(key);
    return true;
}


} // namespace reflectionzeug
