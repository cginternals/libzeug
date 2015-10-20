#pragma once

#include <memory>

#include <signalzeug/signalzeug_api.h>


namespace signalzeug
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
    Connection(const Connection & other);
    Connection(Connection && other);

    Connection & operator=(const Connection & other);
    Connection & operator=(Connection && other);

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

} // namespace signalzeug
