#pragma once

#include <signalzeug.h>

#include <unordered_map>
#include <memory>

class ConnectionHandle;
class ConnectionState;

class SIGNALZEUG_API AbstractSignal
{
public:
	friend class ConnectionHandle;
	typedef int HandleId;

	AbstractSignal();
	virtual ~AbstractSignal();
protected:
	ConnectionHandle createConnectionHandle() const;
	void disconnect(const ConnectionHandle& handle) const;
protected:
	virtual void disconnect(HandleId id) const = 0;
protected:
	mutable HandleId _nextId;
	mutable std::unordered_map<HandleId, std::shared_ptr<ConnectionState>> _states;
};

class SIGNALZEUG_API ConnectionState
{
public:
	friend class AbstractSignal;

	ConnectionState();
	ConnectionState(const AbstractSignal* signal, AbstractSignal::HandleId id);

	const AbstractSignal* signal;
	AbstractSignal::HandleId id;
};

class SIGNALZEUG_API ConnectionHandle
{
public:
	friend class AbstractSignal;

	ConnectionHandle();

	void disconnect();

	AbstractSignal::HandleId id() const;
protected:
	ConnectionHandle(std::shared_ptr<ConnectionState> state);
protected:
	std::shared_ptr<ConnectionState> _state;
};
