
#pragma once


#include <reflectionzeug/new/TypedColor.h>


namespace reflectionzeug
{


template <typename Accessor>
TypedColor<Accessor>::TypedColor(const Accessor & accessor)
: TypedBase<Color, Accessor>(accessor)
{
}

template <typename Accessor>
TypedColor<Accessor>::~TypedColor()
{
}

template <typename Accessor>
Color TypedColor<Accessor>::toColor() const
{
	return this->get();
}

template <typename Accessor>
bool TypedColor<Accessor>::fromColor(const Color & color)
{
    this->set(color);
    return true;
}


} // namespace reflectionzeug
