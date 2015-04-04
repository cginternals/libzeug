
#pragma once


#include <reflectionzeug/new/TypedString.h>


namespace reflectionzeug
{


template <typename Accessor>
TypedString<Accessor>::TypedString(const Accessor & accessor)
: TypedBase<std::string, Accessor>(accessor)
{
}

template <typename Accessor>
TypedString<Accessor>::~TypedString()
{
}

template <typename Accessor>
std::string TypedString<Accessor>::toString() const
{
	return this->get();
}

template <typename Accessor>
bool TypedString<Accessor>::fromString(const std::string & string)
{
	this->set(string);
	return true;
}


} // namespace reflectionzeug
