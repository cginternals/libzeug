#pragma once

#include <signalzeug/Connection.h>

#include <unordered_map>

namespace signal {

class ConnectionMap
{
public:
	ConnectionMap();
	~ConnectionMap();

	template <typename T>
	Connection& operator[](T* object);
protected:
	std::unordered_map<void*, Connection> _connections;

	Connection& get(void* ptr);
};

template <typename T>
Connection& ConnectionMap::operator[](T* object)
{
	return get(static_cast<void*>(object));
}

} // namespace signal
