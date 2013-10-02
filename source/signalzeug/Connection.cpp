#include <Connection.h>
#include <AbstractSignal.h>

namespace signalzeug {

Connection::Connection()
{
}

Connection::Connection(const AbstractSignal* signal, Id id)
: _state(new State{signal, id})
{
}

Connection::Id Connection::id() const
{
	return _state ? _state->id : 0;
}

void Connection::disconnect()
{
	const AbstractSignal* signal = _state ? _state->signal : nullptr;
	if (signal)
	{
		signal->disconnect(*this);
		detach();
	}
}

void Connection::detach()
{
	if (_state)
	{
		_state->signal = nullptr;
	}
}

} // namespace signalzeug
