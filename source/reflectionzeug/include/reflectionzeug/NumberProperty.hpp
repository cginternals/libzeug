#pragma once

#include <reflectionzeug/NumberProperty.h>

#include <limits>
#include <sstream>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

template <typename Type, typename SuperClass>
template <typename... Arguments>
NumberProperty<Type, SuperClass>::NumberProperty(Arguments&&... args)
:   ValueProperty<Type, SuperClass>(std::forward<Arguments>(args)...)
{
    this->setOptions({
        { "minimum", Variant(std::numeric_limits<Type>::min()) },
        { "maximum", Variant(std::numeric_limits<Type>::max()) }
    });
}

template <typename Type, typename SuperClass>
NumberProperty<Type, SuperClass>::~NumberProperty()
{
}

template <typename Type, typename SuperClass>
std::string NumberProperty<Type, SuperClass>::toString() const
{
    return util::toString(this->value());
}

template <typename Type, typename SuperClass>
bool NumberProperty<Type, SuperClass>::fromString(const std::string & string)
{
    if (!util::matchesRegex(string, matchRegex()))
        return false;

    this->setValue(util::fromString<Type>(string));
    return true;
}

} // namespace reflectionzeug
