#pragma once

#include <signalzeug/signalzeug.h>
#include <signalzeug/Connection.h>

#include <unordered_map>

namespace signalzeug {

class SIGNALZEUG_API AbstractSignal
{
public:
	friend class Connection;

	AbstractSignal();
	virtual ~AbstractSignal();
protected:
	Connection createConnection() const;
	void disconnect(Connection& connection) const;
protected:
	virtual void disconnectId(Connection::Id id) const = 0;
protected:
	mutable Connection::Id _nextId;
	mutable std::unordered_map<Connection::Id, Connection> _connections;
};

} // namespace signalzeug
