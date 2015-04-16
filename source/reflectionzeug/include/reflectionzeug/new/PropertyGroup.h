
#pragma once


#include <vector>

#include <reflectionzeug/new/AbstractProperty.h>
#include <reflectionzeug/new/AbstractCollection.h>
#include <reflectionzeug/new/AbstractValue.h>


namespace reflectionzeug
{


template <typename Type>
class Property2;


/**
*  @brief
*    Group of properties
*/
class REFLECTIONZEUG_API PropertyGroup2 : public AbstractProperty2,
                                          public AbstractCollection,
                                          public AbstractValue
{
public:
    signalzeug::Signal<size_t, AbstractProperty2 *> beforeAdd;
    signalzeug::Signal<size_t, AbstractProperty2 *> afterAdd;
    signalzeug::Signal<size_t> beforeRemove;
    signalzeug::Signal<size_t> afterRemove;


public:
    PropertyGroup2();
    PropertyGroup2(const std::string & name);
    virtual ~PropertyGroup2();

    virtual std::string name() const override;
    virtual bool setName(const std::string & name) override;

    // [TODO]
    // virtual Variant toVariant() const override;

    // [TODO]
    // virtual bool fromVariant(const Variant & value) override;

    const std::unordered_map<std::string, AbstractProperty2 *> & properties() const;

    AbstractProperty2 * property(const std::string & path);

    const AbstractProperty2 * property(const std::string & path) const;

    template <typename Type>
    const Property2<Type> * property(const std::string & path) const;

    template <typename Type>
    Property2<Type> * property(const std::string & path);

    AbstractProperty2 * addProperty(AbstractProperty2 * property);

    template <typename Type, typename... Args>
    Property2<Type> * addProperty(const std::string & name, Args&&... args);

    PropertyGroup2 * group(const std::string & path);

    const PropertyGroup2 * group(const std::string & path) const;

    PropertyGroup2 * addGroup(const std::string & name);

    PropertyGroup2 * ensureGroup(const std::string & path);

    template <typename Type>
    Type value(const std::string & path) const;

    template <typename Type>
    void setValue(const std::string & path, const Type & value);

    // AbstractCollection interface
    virtual bool isEmpty() const override;
    virtual size_t count() const override;
    virtual AbstractValue * at(size_t i) override;
    virtual const AbstractValue * at(size_t i) const override;
    virtual int indexOf(const AbstractValue * value) const override;
    virtual void forEach(const std::function<void(AbstractValue &)> & callback) override;
    virtual void forEach(const std::function<void(const AbstractValue &)> & callback) const override;

    /**
     * Removes the property with the given name from the group and returns it.
     */
    AbstractProperty2 * takeProperty(const std::string & name);

    /**
     * Removes all properties from the group. Deletes them if it owns them.
     */
    void clear();

    /**
     * Sets whether the group deletes its properties on destruction or not.
     */
    void setOwnsProperties(bool owns);

    bool propertyExists(const std::string & name) const;
    bool groupExists(const std::string & name) const;

    void forEach(const std::function<void(AbstractProperty2 &)> & callback);
    void forEach(const std::function<void(const AbstractProperty2 &)> & callback) const;

    void forEachCollection(const std::function<void(AbstractCollection &)> & callback);
    void forEachCollection(const std::function<void(const AbstractCollection &)> & callback) const;

    void forEachGroup(const std::function<void(PropertyGroup2 &)> & callback);
    void forEachGroup(const std::function<void(const PropertyGroup2 &)> & callback) const;


protected:
    const AbstractProperty2 * findProperty(const std::vector<std::string> & path) const;
    PropertyGroup2 * ensureGroup(const std::vector<std::string> & path);


protected:
    std::vector<AbstractProperty2 *> m_properties;
    std::unordered_map<std::string, AbstractProperty2 *> m_propertiesMap;
    bool m_ownsProperties;
};


} // namespace reflectionzeug


#include <reflectionzeug/new/PropertyGroup.hpp>