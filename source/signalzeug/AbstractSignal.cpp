#include <AbstractSignal.h>


AbstractSignal::AbstractSignal()
: _nextId(1)
{
}

AbstractSignal::~AbstractSignal()
{
	for (const std::pair<HandleId, std::shared_ptr<ConnectionState>>& pair: _states)
	{
		std::shared_ptr<ConnectionState> state = pair.second;
		state->signal = nullptr;
	}
}

ConnectionHandle AbstractSignal::createConnectionHandle() const
{
	HandleId id = _nextId++;
	std::shared_ptr<ConnectionState> state(new ConnectionState(this, id));
	_states[id] = state;

	return ConnectionHandle(state);
}

void AbstractSignal::disconnect(const ConnectionHandle& handle) const
{
	_states.erase(handle.id());
	disconnect(handle.id());
}

ConnectionState::ConnectionState()
: signal(nullptr)
, id(0)
{
}

ConnectionState::ConnectionState(const AbstractSignal* signal, AbstractSignal::HandleId id)
: signal(signal)
, id(id)
{
}

ConnectionHandle::ConnectionHandle()
{
}

ConnectionHandle::ConnectionHandle(std::shared_ptr<ConnectionState> state)
: _state(state)
{
}

void ConnectionHandle::disconnect()
{
	const AbstractSignal* signal = _state ? _state->signal : nullptr;
	if (signal)
	{
		signal->disconnect(*this);
	}
}

AbstractSignal::HandleId ConnectionHandle::id() const
{
	return _state ? _state->id : 0;
}

