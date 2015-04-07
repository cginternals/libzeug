
#pragma once


#include <reflectionzeug/new/TypedBool.h>


namespace reflectionzeug
{


template <typename... Args>
TypedBool::TypedBool(Args&&... args)
: AbstractTyped<bool>(std::forward<Args>(args)...)
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
