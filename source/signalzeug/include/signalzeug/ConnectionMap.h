#pragma once

#include <unordered_map>

#include <signalzeug/signalzeug.h>
#include <signalzeug/Connection.h>


namespace signalzeug
{

class ConnectionMap
{
public:
	ConnectionMap();
	~ConnectionMap();

	template <typename T>
	Connection & operator[](T * object);

protected:
    Connection & get(void * ptr);

protected:
	std::unordered_map<void *, Connection> m_connections;
};

} // namespace signalzeug

#include "ConnectionMap.hpp"