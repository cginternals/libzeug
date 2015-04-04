
#pragma once


#include <reflectionzeug/new/TypedBool.h>


namespace reflectionzeug
{


template <typename Accessor>
TypedBool<Accessor>::TypedBool(const Accessor & accessor)
: TypedBase<bool, Accessor>(accessor)
{
}

template <typename Accessor>
TypedBool<Accessor>::~TypedBool()
{
}

template <typename Accessor>
void TypedBool<Accessor>::toggleValue()
{
	this->set(!this->get());
}


} // namespace reflectionzeug
