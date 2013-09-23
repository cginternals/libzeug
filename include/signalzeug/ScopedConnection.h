#pragma once

#include <signalzeug/signalzeug.h>

#include <signalzeug/Connection.h>

namespace signal {


class SIGNALZEUG_API ScopedConnection
{
public:
	ScopedConnection();
	ScopedConnection(const Connection& connection);
	~ScopedConnection();

	void operator=(const Connection& connection);
protected:
	Connection _connection;
};

} // namespace signal
