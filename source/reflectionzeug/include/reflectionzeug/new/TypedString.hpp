
#pragma once


#include <reflectionzeug/new/TypedString.h>


namespace reflectionzeug
{


TypedString::TypedString(Accessor<std::string> * accessor)
: TypedBase<std::string>(accessor)
{
}

TypedString::~TypedString()
{
}

std::string TypedString::toString() const
{
	return this->get();
}

bool TypedString::fromString(const std::string & string)
{
	this->set(string);
	return true;
}


} // namespace reflectionzeug
