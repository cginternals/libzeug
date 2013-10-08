
#pragma once

namespace zeug
{

template <typename T>
Connection & ConnectionMap::operator[](T * object)
{
	return get(static_cast<void *>(object));
}

} // namespace zeug
