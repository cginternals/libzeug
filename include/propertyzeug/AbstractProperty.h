
#pragma once


#include <assert.h>
#include <string>

#include <signalzeug/Signal.h>

#include <propertyzeug/propertyzeug.h>

namespace zeug 
{

class AbstractPropertyVisitor;
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
    
    std::string path() const;

    template <class Property>
    Property * to();
    
    template <class Property>
    const Property * to() const;

    virtual bool isGroup() const;
    
    virtual void accept(AbstractPropertyVisitor & visitor) = 0;
    virtual std::string valueAsString() const = 0;

protected:
    std::string m_name;
    std::string m_title;
    std::string m_annotations;

    PropertyGroup * m_parent;
};

} // namespace zeug

#include "AbstractProperty.hpp"
