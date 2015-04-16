
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

    virtual std::string name() const;
    virtual bool setName(const std::string & name);
    bool hasName() const;

    virtual void accept(AbstractVisitor * visitor);
};


} // namespace reflectionzeug