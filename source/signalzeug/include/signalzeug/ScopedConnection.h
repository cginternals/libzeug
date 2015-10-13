#pragma once

#include <signalzeug/signalzeug_api.h>

#include <signalzeug/Connection.h>

namespace signalzeug 
{

class SIGNALZEUG_API ScopedConnection
{
public:
	ScopedConnection();
    ScopedConnection(const Connection & connection);

    ScopedConnection(const ScopedConnection &) = delete;
    ScopedConnection(ScopedConnection && other);

	~ScopedConnection();

    ScopedConnection& operator=(const Connection & connection);

    ScopedConnection& operator=(const ScopedConnection &) = delete;
    ScopedConnection& operator=(ScopedConnection && other);

protected:
	Connection m_connection;
};

} // namespace signalzeug
