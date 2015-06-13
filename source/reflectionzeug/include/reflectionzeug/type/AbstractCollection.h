
#pragma once


#include <functional>

#include <reflectionzeug/reflectionzeug_api.h>


namespace reflectionzeug
{


class AbstractValue;
class AbstractVisitor;


/**
*  @brief
*    Interface for values that are groups of other values
*/
class REFLECTIONZEUG_API AbstractCollection
{
public:
    AbstractCollection();
    virtual ~AbstractCollection();

    virtual bool isEmpty() const = 0;
    virtual size_t count() const = 0;
    virtual AbstractValue * at(size_t i) = 0;
    virtual const AbstractValue * at(size_t i) const = 0;
    virtual int indexOf(const AbstractValue * value) const = 0;

    virtual void forEach(const std::function<void(AbstractValue &)> & callback) = 0;
    virtual void forEach(const std::function<void(const AbstractValue &)> & callback) const = 0;

    void acceptRecursive(AbstractVisitor * visitor);
};


} // namespace reflectionzeug
