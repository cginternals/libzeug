
#pragma once


#include <reflectionzeug/new/TypedColor.h>


namespace reflectionzeug
{


TypedColor::TypedColor(Accessor<Color> * accessor)
: TypedBase<Color>(accessor)
{
}

TypedColor::~TypedColor()
{
}

Color TypedColor::toColor() const
{
	return this->get();
}

bool TypedColor::fromColor(const Color & color)
{
    this->set(color);
    return true;
}


} // namespace reflectionzeug
