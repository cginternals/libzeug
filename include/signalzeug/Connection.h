#pragma once

#include <signalzeug.h>

#include <memory>

namespace signal {

class AbstractSignal;

class SIGNALZEUG_API Connection
{
public:
	friend class AbstractSignal;
	typedef unsigned int Id;

	Connection();

	void disconnect();

	Id id() const;
protected:
	Connection(const AbstractSignal* signal, Id id);

	void detach();
protected:
	struct State
	{
		const AbstractSignal* signal;
		Id id;
	};

	std::shared_ptr<State> _state;
};

} // namespace signal
