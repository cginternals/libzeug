
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
	return this->getValue();
}

bool TypedColor::fromColor(const Color & color)
{
    this->setValue(color);
    return true;
}


} // namespace reflectionzeug
