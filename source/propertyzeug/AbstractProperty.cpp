
#include <propertyzeug/AbstractProperty.h>

#include <regex>
#include <propertyzeug/PropertyGroup.h>

namespace propertyzeug {
    
const std::string AbstractProperty::s_nameRegexString("[a-zA-Z]\\w*");

AbstractProperty::AbstractProperty(const std::string & name)
:   m_name(name)
,   m_title(name)
,   m_announcer(this)
,   m_parent(nullptr)
{
    assert(std::regex_match(m_name, std::regex(s_nameRegexString)));
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
    m_announcer.notify(events::kTitleChanged);
}
    
const std::string & AbstractProperty::annotations() const
{
    return m_annotations;
}

void AbstractProperty::setAnnotations(const std::string & annotations)
{
    m_annotations = annotations;
    m_announcer.notify(events::kAnnotationsChanged);
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
    return m_parent;
}

void AbstractProperty::removeParent()
{
    m_parent = nullptr;
}
    
std::string AbstractProperty::path() const
{
    if (!this->hasParent())
        return this->name();
    
    return this->parent()->path() + "/" + this->name();
}

void AbstractProperty::subscribe(int event, const std::function<void(AbstractProperty &)> & functor)
{
    m_announcer.subscribe(event, functor);
}
    
bool AbstractProperty::isGroup() const
{
    return false;
}

} // namespace
