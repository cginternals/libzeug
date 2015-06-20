
#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/variant/Variant.h>


namespace reflectionzeug
{


class AbstractVisitor;
class AbstractCollection;
class PropertyGroup;


/**
*  @brief
*    Base class for properties
*
*  @remarks
*    When added to a PropertyGroup, the name is used as the unique key.
*
* @see PropertyGroup
*/
class REFLECTIONZEUG_API AbstractProperty
{
public:
    signalzeug::Signal<>                    changed;        ///< Called when the value has been changed
    signalzeug::Signal<const std::string &> optionChanged;  ///< Called when an option of the value has been changed


public:
    //@{
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    */
    AbstractProperty(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractProperty();

    /**
    *  @brief
    *    Get value type
    *
    *  @return
    *    Type id
    */
    virtual const std::type_info & type() const = 0;

    /**
    *  @brief
    *    Check if property has a name
    *
    *  @return
    *    'true' if property has a non-empty name, else 'false'
    */
    bool hasName() const;

    /**
    *  @brief
    *    Get property name
    *
    *  @return
    *    Property name
    */
    std::string name() const;

    /**
    *  @brief
    *    Convert property value to variant
    *
    *    By default, the returned variant has exactly the same type as the property.
    *    However, to support scripting and serialization of properties, a property
    *    specialization of a complex type should implement this function to provide
    *    a conversion into composite values, such as property maps or arrays.
    *
    *  @return
    *    Variant representation
    */
    virtual Variant toVariant() const = 0;

    /**
    *  @brief
    *    Set property value from variant
    *
    *  @param[in] value
    *    Variant representation
    *
    *  @return
    *    'true' if conversion was successful, else 'false'
    */
    virtual bool fromVariant(const Variant & value) = 0;

    /**
    *  @brief
    *    Convert property value to string
    *
    *  @return
    *    String representation
    */
    virtual std::string toString() const = 0;

    /**
    *  @brief
    *    Set property value from string
    *
    *  @param[in] string
    *    String representation
    *
    *  @return
    *    'true' if conversion was successful, else 'false'
    */
    virtual bool fromString(const std::string & string) = 0;

    /**
    *  @brief
    *    Accept a property visitor
    *
    *  @param[in] visitor
    *    Visitor
    */
    virtual void accept(AbstractVisitor * visitor);

    /**
    *  @brief
    *    Check if the property is a collection
    *
    *  @return
    *    'true' if property is derived from AbstractCollection, else 'false'
    */
    bool isCollection() const;

    /**
    *  @brief
    *    Check if the property is a group
    *
    *  @return
    *    'true' if property is derived from PropertyGroup, else 'false'
    */
    bool isGroup() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property as collection
    *
    *  @return
    *    Pointer to AbstractCollection, or nullptr if property isn't a collection
    */
    AbstractCollection * asCollection();
    const AbstractCollection * asCollection() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property as group
    *
    *  @return
    *    Pointer to PropertyGroup, or nullptr if property isn't a group
    */
    PropertyGroup * asGroup();
    const PropertyGroup * asGroup() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property as pointer to base class
    *
    *  @return
    *    Pointer to Type, or nullptr if property isn't of type Type
    */
    template <typename Type>
    Type * as();

    template <typename Type>
    const Type * as() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get options of property
    *
    *    Options provide additional meta information about a property.
    *    Use options to add, e.g., minimum and maximum values,
    *    affixes, or flags. These can be used to configure editor widgets.
    *    Look at the class documentation of the specific property type to
    *    get a list of supported options.
    *
    *  @return
    *    List of options
    */
    const VariantMap & options() const;

    /**
    *  @brief
    *    Set options of property
    *
    *  @param[in] map
    *    List of options
    */
    void setOptions(const VariantMap & map);

    /**
    *  @brief
    *    Check if option is set
    *
    *  @param[in] key
    *    Option name
    *
    *  @return
    *    'true' if the option is set, else 'false'
    */
    bool hasOption(const std::string & key) const;

    /**
    *  @brief
    *    Get option of property
    *
    *  @param[in] key
    *    Option name
    *
    *  @return
    *    Option value
    */
    Variant option(const std::string & key) const;

    /**
    *  @brief
    *    Get option of property convert to a specific type
    *
    *  @param[in] key
    *    Option name
    *  @param[in] defaultValue
    *    Default value
    *
    *  @return
    *    Option value converted to Type, defaultValue if the option doesn't exist or couldn't be converted
    */
    template <typename Type>
    Type option(const std::string & key, const Type & defaultValue) const;

    /**
    *  @brief
    *    Set option of property
    *
    *  @param[in] key
    *    Option name
    *  @param[in] value
    *    Option value
    */
    void setOption(const std::string & key, const Variant & value);

    /**
    *  @brief
    *    Remove option of property
    *
    *  @param[in] key
    *    Option name
    *
    *  @return
    *    'true' if the option has been removed, else 'false'
    */
    bool removeOption(const std::string & key);
    //@}


protected:
    std::string m_name;     ///< Property name
    VariantMap  m_options;  ///< List of options
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractProperty.hpp>
