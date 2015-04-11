
#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class AbstractVisitor;
class AbstractCollection;
class PropertyGroup2;


/**
*  @brief
*    Base class for values
*/
class REFLECTIONZEUG_API AbstractValue
{
public:
    signalzeug::Signal<> valueChanged;  /**< Called when the value has been changed */


public:
    AbstractValue();
    virtual ~AbstractValue();

    virtual std::string name() const;
    virtual bool setName(const std::string & name);
    bool hasName() const;

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

    template <class Type>
    Type * as();

    template <class Type>
    const Type * as() const;

    AbstractCollection * asCollection();
    const AbstractCollection * asCollection() const;

    PropertyGroup2 * asGroup();
    const PropertyGroup2 * asGroup() const;

    bool isCollection() const;
    bool isGroup() const;

    virtual void accept(AbstractVisitor * visitor);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/AbstractValue.hpp>
