
#pragma once

#include <assert.h>
#include <vector>
#include <unordered_map>

#include <propertyzeug/propertyzeug.h>

#include <propertyzeug/Property.h>

namespace zeug {
    
/** @brief
 * Part of the Property Hierarchy.
 * Manages properties while being a property itself.
 */

class PROPERTYZEUG_API PropertyGroup : public AbstractProperty
{
public:
    PropertyGroup(const std::string & name);
    virtual ~PropertyGroup();
    
    virtual bool isGroup() const;
    
    /** @name Property Adding
     * @brief Methods for adding properties.
     */
    /** @{ */
    
    bool addProperty(AbstractProperty * property);
    
    template <typename Type>
    bool addProperty(const std::string & name,
                     const Type & value);
    
    template <typename Type>
    bool addProperty(const std::string & name,
                 const std::function<const Type & ()> & getter,
                 const std::function<void(const Type &)> & setter);
    
    template <typename Type, class Object>
    bool addProperty(const std::string & name,
                 Object & object, const Type & (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(const Type &));
    
    template <typename Type, class Object>
    bool addProperty(const std::string & name,
                 Object & object, Type (Object::*getter_pointer)() const,
                 void (Object::*setter_pointer)(Type));
    
    bool addGroup(const std::string & name);
    
    /** @} */
    
    /** @name Property Accessing
     * @brief Methods accessing properties, subgroups and values.
     * Acces Properties in the hierachy with the separater '/'
     */
    /** @{ */
    
    AbstractProperty * property(const std::string & path);
    const AbstractProperty * property(const std::string & path) const;

    template <typename Type>
    Property<Type> * property(const std::string & path);
    
    template <typename Type>
    const Property<Type> * property(const std::string & path) const;

    PropertyGroup * group(const std::string & path);
    const PropertyGroup * group(const std::string & path) const;

    template <typename Type>
    const Type & value(const std::string & path) const;
    
    template <typename Type>
    void setValue(const std::string & path, const Type & value);
    
    AbstractProperty * property(unsigned int index);
    const AbstractProperty * property(unsigned int index) const;
    
    /** @name Properties
     * @brief Methods for manipulating properties
     */
    /** @{ */

    bool propertyExists(const std::string & name) const;
    bool groupExists(const std::string & name) const;
    
    bool hasProperties() const;
    unsigned int propertyCount() const;
    int indexOfProperty(const std::string & name) const;

    AbstractProperty * obtainProperty(const std::string & name);
    bool removeProperty(AbstractProperty * property);
    
    /** @} */
    
    /** @name Property Iterators
     * @brief Methods for property iteration
     */
    /** @{ */
    
    void forEachProperty(const std::function<void(AbstractProperty &)> functor);
    void forEachProperty(const std::function<void(AbstractProperty &)> functor) const;
    
    void forEachValueProperty(const std::function<void(ValuePropertyBase &)> functor);
    void forEachValueProperty(const std::function<void(ValuePropertyBase &)> functor) const;
    
    void forEachSubGroup(const std::function<void(PropertyGroup &)> functor);
    void forEachSubGroup(const std::function<void(PropertyGroup &)> functor) const;
    
    /** @} */
    
protected:
    std::vector<AbstractProperty *> m_properties;
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;
    
private:
    AbstractProperty * findProperty(const std::string & path);
    const AbstractProperty * findProperty(const std::string & path) const;
};

template <typename Type>
bool PropertyGroup::addProperty(const std::string & name, const Type & value)
{
    return this->addProperty(new Property<Type>(name, value));
}

template <typename Type>
bool PropertyGroup::addProperty(const std::string & name,
    const std::function<const Type & ()> & getter,
    const std::function<void(const Type &)> & setter)
{
    return this->addProperty(new Property<Type>(name, getter, setter));
}

template <typename Type, class Object>
bool PropertyGroup::addProperty(const std::string & name,
    Object & object, const Type & (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(const Type &))
{
    return this->addProperty(new Property<Type>(name, object, getter_pointer, setter_pointer));
}

template <typename Type, class Object>
bool PropertyGroup::addProperty(const std::string & name,
    Object & object, Type (Object::*getter_pointer)() const,
    void (Object::*setter_pointer)(Type))
{
    return this->addProperty(new Property<Type>(name, object, getter_pointer, setter_pointer));
}

template <typename Type>
Property<Type> * PropertyGroup::property(const std::string & name)
{
    return this->property(name)->as<Property<Type>>();
}
    
template <typename Type>
const Property<Type> * PropertyGroup::property(const std::string & name) const
{
    return this->property(name)->as<Property<Type>>();
}

template <typename Type>
const Type & PropertyGroup::value(const std::string & name) const
{
    /** TODO handle non-existence of property **/
    return this->property(name)->as<Property<Type>>()->value();
}

template <typename Type>
void PropertyGroup::setValue(const std::string & name, const Type & value)
{
    /** TODO handle non-existence of property **/
    this->property(name)->as<Property<Type>>()->setValue(value);
}

} // namespace
