#pragma once

#include <vector>
#include <unordered_map>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/property_declaration.h>
#include <reflectionzeug/AbstractPropertyCollection.h>

namespace reflectionzeug
{

class AbstractValueProperty;

/**
 * \brief Property that manages properties while being a property itself.
 *
 * By default, it owns its properties and therefore deletes them on destruction.
 * However you can change this behaviour with setOwnsProperties().
 *
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API PropertyGroup : public AbstractPropertyCollection
{
public:
    PropertyGroup();
    PropertyGroup(const std::string & name);
    virtual ~PropertyGroup();

    virtual bool isGroup() const;

    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;

    /**
     * \name Property Adding
     * \brief Methods for adding properties
     */
    /** \{ */

    AbstractProperty * addProperty(AbstractProperty * property);

    template <typename Type, typename... Args>
    Property<Type> * addProperty(const std::string & name, Args&&... args);

    PropertyGroup * addGroup(const std::string & name);

    /**
     * Convenience method that creates the entire path if it does not exist yet.
     */
    PropertyGroup * ensureGroup(const std::string & path);

    /** \} */

    /**
     * \name Property Accessing
     * \brief Methods for accessing properties, subgroups and values
     * Access Properties in the hierachy with the separator '/'.
    */
    /** \{ */

    AbstractProperty * property(const std::string & path);
    const AbstractProperty * property(const std::string & path) const;

    template <typename Type>
    Property<Type> * property(const std::string & path);

    template <typename Type>
    const Property<Type> * property(const std::string & path) const;

    const std::unordered_map<std::string, AbstractProperty *> & properties() const;

    PropertyGroup * group(const std::string & path);
    const PropertyGroup * group(const std::string & path) const;

    template <typename Type>
    Type value(const std::string & path) const;

    template <typename Type>
    void setValue(const std::string & path, const Type & value);

    /** \} */

    /**
     * \name Index-based Accessing
     * \brief Methods for manipulating properties
     */
    /** \{ */

    virtual AbstractProperty * at(size_t index);
    virtual const AbstractProperty * at(size_t index) const;

    virtual bool isEmpty() const;
    virtual size_t count() const;
    virtual int indexOf(const AbstractProperty * property) const;

    /** \} */

    /**
     * Removes the property with the given name from the group and returns it.
     */
    AbstractProperty * takeProperty(const std::string & name);

    /**
     * Removes all properties from the group. Deletes them if it owns them.
     */
    void clear();

    /**
     * Sets whether the group deletes its properties on destruction or not.
     */
    void setOwnsProperties(bool b);

    /**
     * \name Property existence
     * \brief Methods for checking the existence of properties
     */
    /** \{ */

    bool propertyExists(const std::string & name) const;
    bool groupExists(const std::string & name) const;

    /** \} */

    /**
     * \name Property Iterators
     * \brief Methods for property iteration
     */
    /** \{ */

    virtual void forEach(const std::function<void(AbstractProperty &)> & functor);
    virtual void forEach(const std::function<void(const AbstractProperty &)> & functor) const;

    void forEachValue(const std::function<void(AbstractValueProperty &)> & functor);
    void forEachValue(const std::function<void(const AbstractValueProperty &)> & functor) const;

    void forEachCollection(const std::function<void(AbstractPropertyCollection &)> & functor);
    void forEachCollection(const std::function<void(const AbstractPropertyCollection &)> & functor) const;

    void forEachGroup(const std::function<void(PropertyGroup &)> & functor);
    void forEachGroup(const std::function<void(const PropertyGroup &)> & functor) const;

    /** \} */

    signalzeug::Signal<size_t, AbstractProperty *> beforeAdd;
    signalzeug::Signal<size_t, AbstractProperty *> afterAdd;

    signalzeug::Signal<size_t> beforeRemove;
    signalzeug::Signal<size_t> afterRemove;

private:
    const AbstractProperty * findProperty(const std::vector<std::string> & path) const;
    PropertyGroup * ensureGroup(const std::vector<std::string> & path);

private:
    std::vector<AbstractProperty *> m_properties;
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;
    bool m_ownsProperties;
};

} // namespace reflectionzeug

#include <reflectionzeug/PropertyGroup.hpp>
