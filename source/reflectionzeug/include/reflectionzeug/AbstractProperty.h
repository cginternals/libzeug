
#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/Variant.h>


namespace reflectionzeug
{


class AbstractValue;
class AbstractCollection;
class PropertyGroup;


/**
*  @brief
*    Base class for properties
*/
class REFLECTIONZEUG_API AbstractProperty
{
public:
    signalzeug::Signal<const std::string &> optionChanged;


public:
    AbstractProperty();
    virtual ~AbstractProperty();

    bool isValue() const;
    bool isCollection() const;
    bool isGroup() const;

    AbstractValue * asValue();
    const AbstractValue * asValue() const;

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


private:
    VariantMap m_options;
};


} // namespace reflectionzeug


#include <reflectionzeug/AbstractProperty.hpp>
