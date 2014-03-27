
#pragma once

#include <vector>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValuePropertyInterface.h>

namespace reflectionzeug
{

template <typename Type>
class ArrayPropertyInterface : public virtual ValuePropertyInterface
{
public:
    ArrayPropertyInterface(const std::string & name);
    
    virtual void accept(AbstractPropertyVisitor * visitor, bool warn = true);
    
    virtual unsigned int size() const = 0;

    virtual unsigned int columns() const = 0;
    virtual unsigned int rows() const = 0;

    virtual std::vector<Type> toVector() const = 0;
    virtual bool fromVector(const std::vector<Type> & vector) = 0;

};

} // namespace reflectionzeug

#include "ArrayPropertyInterface.hpp"
