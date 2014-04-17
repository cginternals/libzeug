
#pragma once

#include <assert.h>
#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug.h>

namespace reflectionzeug
{

class AbstractValueProperty;
class AbstractPropertyGroup;
    
/** \brief Part of the property hierarchy (base class of all properties).
*/
class REFLECTIONZEUG_API AbstractProperty 
{
public:
    static const std::string s_nameRegexString;
    
    AbstractProperty();
    AbstractProperty(const std::string & name);
    
    virtual ~AbstractProperty() = 0;

    const std::string & name() const;
    
    const std::string & title() const;
    void setTitle(const std::string & title);
    
    const std::string & annotations() const;
    void setAnnotations(const std::string & annotations);
    
    AbstractPropertyGroup * parent() const;
    void setParent(AbstractPropertyGroup * parent);
    void removeParent();
    bool hasParent() const;
    
    bool isEnabled() const;
    void setEnabled(bool enabled);
    
    std::string path() const;

    template <class Property>
    Property * as();
    
    template <class Property>
    const Property * as() const;

    AbstractValueProperty * asValue();
    const AbstractValueProperty * asValue() const;

    AbstractPropertyGroup * asGroup();
    const AbstractPropertyGroup * asGroup() const;

    virtual bool isGroup() const;
    virtual bool isValue() const;
    virtual bool isArray() const;
    
private:
    enum class State : char { NotSet, Enabled, Disabled };
    
    State m_state;
    
    std::string m_name;
    std::string m_title;
    std::string m_annotations;

    AbstractPropertyGroup * m_parent;
};
    
} // namespace reflectionzeug

#include "AbstractProperty.hpp"
