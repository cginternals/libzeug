
#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <propertyzeug/ValueProperty.h>
#include <propertyzeug/PropertyGroup.h>

#include <propertyzeug/AbstractProperty.h>

namespace zeug {
    
const std::string AbstractProperty::s_nameRegexString("[a-zA-Z]+[\\s,\\w]*");

AbstractProperty::AbstractProperty(const std::string & name)
:   m_name(name)
,   m_title(name)
,   m_parent(nullptr)
,   m_state(kNotSet)
{
    assert(regex_namespace::regex_match(m_name, regex_namespace::regex(s_nameRegexString)));
}

AbstractProperty::~AbstractProperty()
{
}

const std::string & AbstractProperty::name() const
{
    return m_name;
}

const std::string & AbstractProperty::title() const
{
    return m_title;
}

void AbstractProperty::setTitle(const std::string & title)
{
    m_title = title;
}
    
const std::string & AbstractProperty::annotations() const
{
    return m_annotations;
}

void AbstractProperty::setAnnotations(const std::string & annotations)
{
    m_annotations = annotations;
}
    
PropertyGroup * AbstractProperty::parent() const
{
    return m_parent;
}
    
void AbstractProperty::setParent(PropertyGroup * parent)
{
    m_parent = parent;
}

bool AbstractProperty::hasParent() const
{
    return nullptr != m_parent;
}

void AbstractProperty::removeParent()
{
    m_parent = nullptr;
}
    
bool AbstractProperty::isEnabled() const
{
    if (m_state != kNotSet)
        return m_state == kEnabled;
    
    if (!this->hasParent())
        return true;

    return this->parent()->isEnabled();
}
    
void AbstractProperty::setEnabled(bool enabled)
{
    m_state = enabled ? kEnabled : kDisabled;
}
    
std::string AbstractProperty::path() const
{
    if (!this->hasParent())
        return this->name();
    
    return this->parent()->path() + "/" + this->name();
}
    
ValueProperty * AbstractProperty::asValue()
{
    return static_cast<ValueProperty *>(this);
}

const ValueProperty * AbstractProperty::asValue() const
{
    return static_cast<const ValueProperty *>(this);
}

PropertyGroup * AbstractProperty::asGroup()
{
    return static_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractProperty::asGroup() const
{
    return static_cast<const PropertyGroup *>(this);
}
    
bool AbstractProperty::isGroup() const
{
    return false;
}

} // namespace zeug
