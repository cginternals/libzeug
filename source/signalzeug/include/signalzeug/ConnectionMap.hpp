
#pragma once

#include <signalzeug/ConnectionMap.h>

namespace signalzeug
{

template <typename T>
Connection & ConnectionMap::operator[](T * object)
{
	return get(static_cast<void *>(object));
}

} // namespace signalzeug
