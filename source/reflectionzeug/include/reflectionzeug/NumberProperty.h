
#pragma once

#include <reflectionzeug/ValuePropertyTemplate.h>

namespace reflectionzeug
{

/** \brief Part of the property hierarchy that extends the ValuePropertyTemplate by adding a minimum and maximum.
 */
template <typename Type>
class NumberProperty : public ValuePropertyTemplate<Type>
{
public:
    NumberProperty(const std::string & name, const Type & value);

    NumberProperty(const std::string & name,
                   const std::function<Type ()> & getter,
                   const std::function<void(const Type &)> & setter);

    template <class Object>
    NumberProperty(const std::string & name,
                   Object & object, const Type & (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    template <class Object>
    NumberProperty(const std::string & name,
                   Object & object, Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(const Type &));

    template <class Object>
    NumberProperty(const std::string & name,
                   Object & object, Type (Object::*getter_pointer)() const,
                   void (Object::*setter_pointer)(Type));

    const Type & minimum() const;
    void setMinimum(const Type & minimum);
    bool hasMinimum() const;

    const Type & maximum() const;
    void setMaximum(const Type & maximum);
    bool hasMaximum() const;

    void setRange(const Type & minimum, const Type & maximum);
    bool hasRange() const;

    const Type & step() const;
    void setStep(const Type & step);
    bool hasStep() const;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

protected:
    virtual std::string stringMatch() = 0;

protected:
    Type m_min;
    Type m_max;
    Type m_step;
};

} // namespace reflectionzeug

#include "NumberProperty.hpp"
