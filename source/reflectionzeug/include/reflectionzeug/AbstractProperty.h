
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
 * Do not change its name when it's in one or more groups.
 * All subclasses use virtual inheritance.
 *
 * \see PropertyGroup
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API AbstractProperty 
{
public:
    static const std::string s_nameRegexString;
    
    AbstractProperty();
    AbstractProperty(const std::string & name);
    
    virtual ~AbstractProperty() = 0;

    const std::string & name() const;
    bool setName(const std::string & name);
    bool hasName() const;
    
    const std::string & title() const;
    void setTitle(const std::string & title);
    bool hasTitle() const;
    
    const std::string & annotations() const;
    void setAnnotations(const std::string & annotations);
    
    bool isEnabled() const;
    void setEnabled(bool enabled);

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
    
};
    
} // namespace reflectionzeug

#include "AbstractProperty.hpp"
