
#pragma once

#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{

/**
 * \brief An intermediate class for numeric property types.
 *
 * Adds a minimum and maximum as well as a step size.
 */
template <typename Type>
class NumberProperty : public ValueProperty<Type>
{
public:
    template <typename... Arguments>
    NumberProperty(Arguments&&... args);

    virtual ~NumberProperty() = 0;

    const Type & minimum() const;
    void setMinimum(const Type & minimum);
    virtual bool hasMinimum() const;

    const Type & maximum() const;
    void setMaximum(const Type & maximum);
    virtual bool hasMaximum() const;

    void setRange(const Type & minimum, const Type & maximum);
    virtual bool hasRange() const;

    const Type & step() const;
    void setStep(const Type & step);
    virtual bool hasStep() const;

    virtual std::string toString() const;
    virtual bool fromString(const std::string & string);

protected:
    virtual std::string matchRegex() const = 0;

protected:
    Type m_min;
    Type m_max;
    Type m_step;
};

} // namespace reflectionzeug

#include "NumberProperty.hpp"
