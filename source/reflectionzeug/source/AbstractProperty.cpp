
#include <reflectionzeug/type/AbstractValue.h>
#include <reflectionzeug/type/AbstractCollection.h>
#include <reflectionzeug/AbstractProperty.h>
#include <reflectionzeug/PropertyGroup.h>


namespace reflectionzeug
{


AbstractProperty::AbstractProperty()
{
}

AbstractProperty::~AbstractProperty()
{
}

bool AbstractProperty::isValue() const
{
    return (dynamic_cast<const AbstractValue *>(this) != nullptr);
}

bool AbstractProperty::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractProperty::isGroup() const
{
    return (dynamic_cast<const PropertyGroup *>(this) != nullptr);
}

AbstractValue * AbstractProperty::asValue()
{
    return dynamic_cast<AbstractValue *>(this);
}

const AbstractValue * AbstractProperty::asValue() const
{
    return dynamic_cast<const AbstractValue *>(this);
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
