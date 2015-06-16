
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
*    Base class for values
*/
class REFLECTIONZEUG_API AbstractProperty
{
public:
    signalzeug::Signal<> 					changed;  		/**< Called when the value has been changed */
    signalzeug::Signal<const std::string &> optionChanged;	/**< Called when an option of the value has been changed */


public:
    AbstractProperty(const std::string & name);
    virtual ~AbstractProperty();

    virtual const std::type_info & type() const = 0;

    std::string name() const;
    bool hasName() const;

    virtual Variant toVariant() const = 0;
    virtual bool fromVariant(const Variant & value) = 0;

    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & string) = 0;

    virtual void accept(AbstractVisitor * visitor);

    bool isCollection() const;
    bool isGroup() const;

    AbstractCollection * asCollection();
    const AbstractCollection * asCollection() const;

    PropertyGroup * asGroup();
    const PropertyGroup * asGroup() const;

    template <typename Type>
    Type * as();

    template <typename Type>
    const Type * as() const;

    const VariantMap & options() const;
    Variant option(const std::string & key) const;

    template <typename Type>
    Type option(const std::string & key, const Type & defaultValue) const;

    bool hasOption(const std::string & key) const;

    void setOption(const std::string & key, const Variant & value);
    void setOptions(const VariantMap & map);

    bool removeOption(const std::string & key);


protected:
    std::string m_name;
    VariantMap  m_options;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/AbstractProperty.hpp>
