
#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug_api.h>


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

    /* [TODO]
    virtual Variant toVariant() const;
    virtual bool fromVariant(const Variant & value);
    */

    virtual void accept(AbstractVisitor * visitor);
};


} // namespace reflectionzeug
