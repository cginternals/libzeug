
#pragma once


#include <reflectionzeug/new/TypedBool.h>


namespace reflectionzeug
{


TypedBool::TypedBool(Accessor<bool> * accessor)
: TypedBase<bool>(accessor)
{
}

TypedBool::~TypedBool()
{
}

void TypedBool::toggleValue()
{
	this->setValue(!this->getValue());
}


} // namespace reflectionzeug
