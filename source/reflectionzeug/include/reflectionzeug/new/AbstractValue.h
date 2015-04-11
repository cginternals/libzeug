
#pragma once


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
    AbstractValue();
    virtual ~AbstractValue();

    virtual void accept(AbstractVisitor * visitor);
};


} // namespace reflectionzeug
