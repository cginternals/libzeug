
#pragma once


#include <assert.h>
#include <string>

#include <signalzeug/Signal.h>

#include <propertyzeug/propertyzeug.h>

namespace zeug 
{

class AbstractPropertyVisitor;
class ValueProperty;
class PropertyGroup;
    
/** @brief
 * Part of the property hierarchy.
 * The base class of all properties.
 */

class PROPERTYZEUG_API AbstractProperty 
{
public:
    static const std::string s_nameRegexString;
    
    AbstractProperty(const std::string & name);
    virtual ~AbstractProperty();

    const std::string & name() const;
    
    const std::string & title() const;
    void setTitle(const std::string & title);
    
    const std::string & annotations() const;
    void setAnnotations(const std::string & annotations);
    
    PropertyGroup * parent() const;
    void setParent(PropertyGroup * parent);
    void removeParent();
    bool hasParent() const;
    
    bool isEnabled() const;
    void setEnabled(bool enabled);
    
    std::string path() const;

    template <class Property>
    Property * as();
    
    template <class Property>
    const Property * as() const;

    ValueProperty * asValue();
    const ValueProperty * asValue() const;

    PropertyGroup * asGroup();
    const PropertyGroup * asGroup() const;

    virtual bool isGroup() const;

protected:
    enum {
        kNotSet,
        kEnabled,
        kDisabled
    } m_state;
    
    std::string m_name;
    std::string m_title;
    std::string m_annotations;

    PropertyGroup * m_parent;
};
    
} // namespace zeug

#include "AbstractProperty.hpp"
