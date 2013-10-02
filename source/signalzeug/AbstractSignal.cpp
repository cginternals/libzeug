#include <AbstractSignal.h>

namespace signal {

AbstractSignal::AbstractSignal()
: _nextId(1)
{
}

AbstractSignal::~AbstractSignal()
{
	for (std::pair<Connection::Id, Connection> pair: _connections)
	{
		Connection& connection = pair.second;
		connection.detach();
	}
}

Connection AbstractSignal::createConnection() const
{
	Connection::Id id = _nextId++;
	Connection connection(this, id);
	_connections[id] = connection;

	return connection;
}

void AbstractSignal::disconnect(Connection& connection) const
{
	_connections.erase(connection.id());
	disconnectId(connection.id());
}

} // namespace signal
