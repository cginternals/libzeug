
#pragma once

#include <reflectionzeug/reflectionzeug_api.h>
#include <reflectionzeug/AbstractValueProperty.h>


namespace reflectionzeug
{

/**
 * \brief The interface for all signed integral properties. 
 *
 * Used to access and edit signed integral properties uniformly in the user interface.
 *
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API SignedIntegralPropertyInterface : public virtual AbstractValueProperty
{
public:    
    virtual void accept(AbstractPropertyVisitor * visitor);
    
    virtual long long uLongLongMinimum() = 0;
    virtual bool hasMinimum() const = 0;

    virtual long long uLongLongMaximum() = 0;
    virtual bool hasMaximum() const = 0;

    virtual bool hasRange() const = 0;

    virtual long long uLongLongStep() = 0;
    virtual bool hasStep() const = 0;

    virtual long long toULongLong() const = 0;
    virtual bool fromULongLong(long long integral) = 0;

};

} // namespace reflectionzeug
