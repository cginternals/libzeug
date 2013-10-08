#pragma once

#include <memory>

#include <signalzeug/signalzeug.h>


namespace zeug
{

class AbstractSignal;

class SIGNALZEUG_API Connection
{
	friend class AbstractSignal;

public:
    typedef unsigned int Id;


protected:
    struct State
	{
		const AbstractSignal * signal;
		Id id;
	};

public:
	Connection();

	void disconnect();

	Id id() const;

protected:
    Connection(
        const AbstractSignal * signal
    ,   Id id);

	void detach();

protected:
	std::shared_ptr<State> m_state;
};

} // namespace zeug
