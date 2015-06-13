#pragma once

#include <reflectionzeug/AbstractProperty.h>

namespace reflectionzeug
{

/**
 * \brief The super class of all property collections.
 * \ingroup property_hierarchy
 */
class REFLECTIONZEUG_API AbstractPropertyCollection : public virtual AbstractProperty
{
public:
    virtual bool isCollection() const;

    virtual AbstractProperty * at(size_t i) = 0;
    virtual const AbstractProperty * at(size_t i) const = 0;

    virtual bool isEmpty() const = 0;
    virtual size_t count() const = 0;
    virtual int indexOf(const AbstractProperty * property) const = 0;

    virtual void forEach(const std::function<void(AbstractProperty &)> & functor) = 0;
    virtual void forEach(const std::function<void(const AbstractProperty &)> & functor) const = 0;
};

} // namespace reflectionzeug
