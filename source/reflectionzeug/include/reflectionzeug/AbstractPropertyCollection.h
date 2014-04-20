
#pragma once

#include <reflectionzeug/AbstractProperty.h>


namespace reflectionzeug
{

class REFLECTIONZEUG_API AbstractPropertyCollection : public virtual AbstractProperty
{
public:
    virtual bool isCollection() const;

    virtual AbstractProperty * at(size_t i) = 0;
    virtual const AbstractProperty * at(size_t i) const = 0;

    virtual bool isEmpty() const = 0;
    virtual size_t count() const = 0;
    virtual int indexOf(const AbstractProperty * property) const = 0;

};

} // namespace relfectionzeug
