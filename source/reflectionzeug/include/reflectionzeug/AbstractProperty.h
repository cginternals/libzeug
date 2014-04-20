
#pragma once

#include <assert.h>
#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug.h>

namespace reflectionzeug
{

class AbstractValueProperty;
class AbstractPropertyCollection;
class PropertyGroup;
    
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
    
    AbstractPropertyCollection * parent() const;
    void setParent(AbstractPropertyCollection * parent);
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

    AbstractPropertyCollection * asCollection();
    const AbstractPropertyCollection * asCollection() const;

    PropertyGroup * asGroup();
    const PropertyGroup * asGroup() const;

    virtual bool isCollection() const;
    virtual bool isValue() const;
    virtual bool isGroup() const;
    
private:
    enum class State : char { NotSet, Enabled, Disabled };
    
    State m_state;
    
    std::string m_name;
    std::string m_title;
    std::string m_annotations;

    AbstractPropertyCollection * m_parent;
};
    
} // namespace reflectionzeug

#include "AbstractProperty.hpp"
