
#pragma once

#include <limits>
#include <sstream>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
NumberProperty<Type>::NumberProperty(Arguments&&... args)
:   ValueProperty<Type>(std::forward<Arguments>(args)...)
,   m_min(std::numeric_limits<Type>::lowest())
,   m_max(std::numeric_limits<Type>::max())
,   m_step(0)
{
}

template <typename Type>
NumberProperty<Type>::~NumberProperty()
{
}

template <typename Type>
const Type & NumberProperty<Type>::minimum() const
{
    return m_min;
}

template <typename Type>
void NumberProperty<Type>::setMinimum(const Type & minimum)
{
    m_min = minimum;
}

template <typename Type>
bool NumberProperty<Type>::hasMinimum() const
{
    return m_min != std::numeric_limits<Type>::lowest();
}

template <typename Type>
const Type & NumberProperty<Type>::maximum() const
{
    return m_max;
}

template <typename Type>
void NumberProperty<Type>::setMaximum(const Type & maximum)
{
    m_max = maximum;
}

template <typename Type>
bool NumberProperty<Type>::hasMaximum() const
{
    return m_max != std::numeric_limits<Type>::max();
}

template <typename Type>
void NumberProperty<Type>::setRange(const Type & minimum, const Type & maximum)
{
    m_min = minimum;
    m_max = maximum;
}

template <typename Type>
bool NumberProperty<Type>::hasRange() const
{
    return hasMinimum() && hasMaximum();
}

template <typename Type>
const Type & NumberProperty<Type>::step() const
{
    return m_step;
}

template <typename Type>
void NumberProperty<Type>::setStep(const Type & step)
{
    m_step = step;
}

template <typename Type>
bool NumberProperty<Type>::hasStep() const
{
    return m_step != 0;
}

template <typename Type>
std::string NumberProperty<Type>::toString() const
{
    return util::toString(this->value());
}

template <typename Type>
bool NumberProperty<Type>::fromString(const std::string & string)
{
    if (!util::matchesRegex(string, matchRegex()))
        return false;

    this->setValue(util::fromString<Type>(string));
    return true;
}

} // namespace reflectionzeug
