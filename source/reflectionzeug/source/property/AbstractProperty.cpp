
#include <reflectionzeug/property/AbstractProperty.h>

#include <reflectionzeug/property/AbstractValueProperty.h>
#include <reflectionzeug/property/AbstractCollection.h>
#include <reflectionzeug/property/PropertyGroup.h>


namespace reflectionzeug
{


const std::string AbstractProperty::s_nameRegexString("[a-zA-Z_]+\\w*");


AbstractProperty::AbstractProperty(const std::string & name)
: m_name(name)
{
}

AbstractProperty::~AbstractProperty()
{
}

bool AbstractProperty::hasName() const
{
    return !m_name.empty();
}

std::string AbstractProperty::name() const
{
    return m_name;
}

void AbstractProperty::accept(AbstractVisitor * /*visitor*/)
{
}

bool AbstractProperty::isValue() const
{
    return (dynamic_cast<const AbstractValueProperty *>(this) != nullptr);
}

bool AbstractProperty::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractProperty::isGroup() const
{
    return (dynamic_cast<const PropertyGroup *>(this) != nullptr);
}

AbstractValueProperty * AbstractProperty::asValue()
{
    return dynamic_cast<AbstractValueProperty *>(this);
}

const AbstractValueProperty * AbstractProperty::asValue() const
{
    return dynamic_cast<const AbstractValueProperty *>(this);
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

void AbstractProperty::setOptions(const VariantMap & map)
{
    for (const auto & pair : map)
    {
        m_options[pair.first] = pair.second;
        optionChanged(pair.first);
    }
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
    optionChanged(key);
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
