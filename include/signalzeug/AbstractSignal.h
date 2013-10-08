#pragma once

#include <signalzeug/signalzeug.h>
#include <signalzeug/Connection.h>

#include <unordered_map>

namespace zeug
{

class SIGNALZEUG_API AbstractSignal
{
    friend class Connection;

public:
	AbstractSignal();
	virtual ~AbstractSignal();

protected:
	Connection createConnection() const;
	void disconnect(Connection & connection) const;

protected:
	virtual void disconnectId(Connection::Id id) const = 0;

protected:
	mutable Connection::Id m_nextId;
	mutable std::unordered_map<Connection::Id, Connection> m_connections;
};

} // namespace zeug
