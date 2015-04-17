
#pragma once


#include <string>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class AbstractValue;
class AbstractCollection;
class PropertyGroup2;


/**
*  @brief
*    Base class for properties
*/
class REFLECTIONZEUG_API AbstractProperty2
{
public:
    AbstractProperty2();
    virtual ~AbstractProperty2();

    bool isValue() const;
    bool isCollection() const;
    bool isGroup() const;

    AbstractValue * asValue();
    const AbstractValue * asValue() const;

    AbstractCollection * asCollection();
    const AbstractCollection * asCollection() const;

    PropertyGroup2 * asGroup();
    const PropertyGroup2 * asGroup() const;

    template <class Type>
    Type * as();

    template <class Type>
    const Type * as() const;

    // [TODO]
    /*
    const VariantMap & options() const;
    Variant option(const std::string & key) const;

    template <typename T>
    T option(const std::string & key, const T & defaultValue) const;

    bool hasOption(const std::string & key) const;

    void setOption(const std::string & key, const Variant & value);
    void setOptions(const VariantMap & map);

    bool removeOption(const std::string & key);
    */
};


} // namespace reflectionzeug


#include <reflectionzeug/new/AbstractProperty.hpp>
