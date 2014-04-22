
#pragma once

#include <assert.h>
#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>

namespace reflectionzeug
{

class AbstractValueProperty;
class AbstractPropertyCollection;
class PropertyGroup;
    
/** 
 * \brief The base class of all properties.
 *
 * When added to a PropertyGroup, the name is used as the unique key.
 * The title is supposed to be used in user interfaces.
 * Most subclasses use virtual inheritance.
 * \see PropertyGroup
 */
class REFLECTIONZEUG_API AbstractProperty 
{
public:
    static const std::string s_nameRegexString;
    
    /**
     * Should never be used.
     * Exists just to avoid explicit constructor calls in intermediate subclasses.
     */
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

    /**
     * \name Convenience casting methods
     * Use them, when you need to cast to sub classes.
     * All casting is done with dynamic casts.
     */
    /** \{ */
    
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
    
    /** \} */
    
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
