
#pragma once

#include <functional>

#include <reflectionzeug/AbstractArrayValue.h>


namespace reflectionzeug
{

/**
 * \brief Provides access to an array value by element-based accessors.
 */
template <typename Type, size_t Size>
class AccessorArrayValue : public AbstractArrayValue<Type, Size>
{
public:
    AccessorArrayValue(const std::function<Type (size_t)> & getter,
                       const std::function<void(size_t, const Type &)> & setter);
    
    template <class Object>
    AccessorArrayValue(Object * object,
                       const Type & (Object::*getter_pointer)(size_t) const,
                       void (Object::*setter_pointer)(size_t, const Type &));
    
    template <class Object>
    AccessorArrayValue(Object * object,
                       Type (Object::*getter_pointer)(size_t) const,
                       void (Object::*setter_pointer)(size_t, const Type &));

    template <class Object>
    AccessorArrayValue(Object * object,
                       Type (Object::*getter_pointer)(size_t) const,
                       void (Object::*setter_pointer)(size_t, Type));

    virtual std::array<Type, Size> get() const;
    virtual void set(const std::array<Type, Size> & array);

    virtual Type get(size_t i) const;
    virtual void set(size_t i, const Type & value);
    
private:
    std::function<Type (size_t)> m_getter;
    std::function<void(size_t, const Type &)> m_setter;

};

} // namespace reflectionzeug

#include "AccessorArrayValue.hpp"
