
#pragma once


#include <assert.h>
#include <string>

#include <signalzeug/Signal.h>

#include <propertyzeug/propertyzeug.h>

namespace zeug 
{

class AbstractPropertyVisitor;
class ValuePropertyBase;
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

    bool isActive() const;
    void setActive(bool active);
    void activate();
    void deactivate();
    
    
    std::string path() const;

    template <class Property>
    Property * as();
    
    template <class Property>
    const Property * as() const;

    ValuePropertyBase * asValueProperty();
    const ValuePropertyBase * asValueProperty() const;

    PropertyGroup * asGroup();
    const PropertyGroup * asGroup() const;

    virtual bool isGroup() const;
    
    virtual void accept(AbstractPropertyVisitor & visitor) = 0;
    virtual std::string valueAsString() const = 0;

protected:
    std::string m_name;
    std::string m_title;
    std::string m_annotations;

    bool m_active;

    PropertyGroup * m_parent;
};
    
} // namespace zeug

#include "AbstractProperty.hpp"
