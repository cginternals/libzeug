
#include <reflectionzeug/type/AbstractValue.h>
#include <reflectionzeug/type/AbstractCollection.h>
#include <reflectionzeug/PropertyGroup.h>


namespace reflectionzeug
{


AbstractValue::AbstractValue()
{
}

AbstractValue::~AbstractValue()
{
}

std::string AbstractValue::name() const
{
    // Not implemented for base class
    return "";
}

bool AbstractValue::hasName() const
{
    return !name().empty();
}

void AbstractValue::accept(AbstractVisitor * visitor)
{
}

bool AbstractValue::isCollection() const
{
    return (dynamic_cast<const AbstractCollection *>(this) != nullptr);
}

bool AbstractValue::isGroup() const
{
    return (dynamic_cast<const PropertyGroup *>(this) != nullptr);
}

AbstractCollection * AbstractValue::asCollection()
{
    return dynamic_cast<AbstractCollection *>(this);
}

const AbstractCollection * AbstractValue::asCollection() const
{
    return dynamic_cast<const AbstractCollection *>(this);
}

PropertyGroup * AbstractValue::asGroup()
{
    return dynamic_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractValue::asGroup() const
{
    return dynamic_cast<const PropertyGroup *>(this);
}

const VariantMap & AbstractValue::options() const
{
    return m_options;
}

Variant AbstractValue::option(const std::string & key) const
{
    if (!this->hasOption(key))
        return Variant();

    return m_options.at(key);
}

bool AbstractValue::hasOption(const std::string & key) const
{
    return m_options.count(key) != 0;
}

void AbstractValue::setOption(const std::string & key, const Variant & value)
{
    m_options[key] = value;
    optionChanged(key);
}

void AbstractValue::setOptions(const VariantMap & map)
{
    for (const auto & pair : map)
    {
        m_options[pair.first] = pair.second;
        optionChanged(pair.first);
    }
}

bool AbstractValue::removeOption(const std::string & key)
{
    if (!this->hasOption(key))
        return false;

    m_options.erase(key);
    optionChanged(key);
    return true;
}


} // namespace reflectionzeug
