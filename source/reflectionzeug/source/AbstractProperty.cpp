
#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/AbstractPropertyCollection.h>
#include <reflectionzeug/PropertyGroup.h>

#include <reflectionzeug/AbstractProperty.h>


namespace reflectionzeug 
{
    
const std::string AbstractProperty::s_nameRegexString("[a-zA-Z_]+\\w*");

AbstractProperty::AbstractProperty()
{
    // should never be called; just to avoid explicit constructor call in each subclass
    assert(false);
}

AbstractProperty::AbstractProperty(const std::string & name)
:   m_state(State::NotSet)
,   m_name(name)
,   m_title(name)
,   m_parent(nullptr)
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
    
AbstractPropertyCollection * AbstractProperty::parent() const
{
    return m_parent;
}
    
void AbstractProperty::setParent(AbstractPropertyCollection * parent)
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
    if (m_state != State::NotSet)
        return m_state == State::Enabled;
    
    if (!this->hasParent())
        return true;

    return this->parent()->isEnabled();
}
    
void AbstractProperty::setEnabled(bool enabled)
{
    m_state = enabled ? State::Enabled : State::Disabled;
}
    
std::string AbstractProperty::path() const
{
    if (!this->hasParent())
        return this->name();
    
    return this->parent()->path() + "/" + this->name();
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
