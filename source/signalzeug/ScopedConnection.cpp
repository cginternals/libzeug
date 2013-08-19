#include <ScopedConnection.h>


namespace signal {

ScopedConnection::ScopedConnection()
{
}

ScopedConnection::ScopedConnection(const Connection& connection)
: _connection(connection)
{
}

ScopedConnection::~ScopedConnection()
{
	_connection.disconnect();
}

void ScopedConnection::operator=(const Connection& connection)
{
	_connection.disconnect();
	_connection = connection;
}

} // namespace signal
