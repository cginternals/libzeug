
#pragma once


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
    signalzeug::Signal<> valueChanged;	/**< Called when the value has been changed */


public:
    AbstractValue();
    virtual ~AbstractValue();

    virtual void accept(AbstractVisitor * visitor);
};


} // namespace reflectionzeug
