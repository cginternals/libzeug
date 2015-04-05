
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
	return this->getValue();
}

bool TypedString::fromString(const std::string & string)
{
	this->setValue(string);
	return true;
}


} // namespace reflectionzeug
