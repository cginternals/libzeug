#pragma once

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief The interface for all unsigned integral properties. 
 *
 * Used to access and edit unsigned integral properties uniformly in the user interface.
 *
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API UnsignedIntegralPropertyInterface : public virtual AbstractValueProperty
{
public:    
    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual unsigned long long toULongLong() const = 0;
    virtual bool fromULongLong(unsigned long long integral) = 0;
};

} // namespace reflectionzeug
