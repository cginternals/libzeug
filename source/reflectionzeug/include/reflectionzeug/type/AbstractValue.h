
#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/Variant.h>


namespace reflectionzeug
{


class AbstractVisitor;


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

    virtual const std::type_info & type() const = 0;

    virtual std::string name() const;
    bool hasName() const;

    virtual Variant toVariant() const = 0;
    virtual bool fromVariant(const Variant & value) = 0;

    virtual void accept(AbstractVisitor * visitor);
};


} // namespace reflectionzeug
