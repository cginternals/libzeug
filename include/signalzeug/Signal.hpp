#pragma once

#include <signalzeug/AbstractSignal.h>

#include <functional>
#include <unordered_map>

namespace signalzeug {

template <typename... Arguments>
class SIGNALZEUG_API Signal : public AbstractSignal
{
public:
	typedef std::function<void(Arguments...)> Callback;

	Signal();

	void fire(Arguments... arguments);
	void operator()(Arguments... arguments);

	Connection connect(Callback callback) const;
	template <class T>
	Connection connect(T* object, void (T::*method)(Arguments...)) const;
protected:
	virtual void disconnectId(Connection::Id id) const override;
protected:
	mutable std::unordered_map<Connection::Id, Callback> _callbacks;
};


template <typename... Arguments>
Signal<Arguments...>::Signal()
{
}

template <typename... Arguments>
void Signal<Arguments...>::fire(Arguments... arguments)
{
	for (const std::pair<Connection::Id, Callback>& pair: _callbacks)
	{
		Callback callback = pair.second;
		callback(arguments...);
	}
}

template <typename... Arguments>
void Signal<Arguments...>::operator()(Arguments... arguments)
{
	fire(arguments...);
}

template <typename... Arguments>
Connection Signal<Arguments...>::connect(Callback callback) const
{
	Connection connection = createConnection();
	_callbacks[connection.id()] = callback;
	return connection;
}

template <typename... Arguments>
template <class T>
Connection Signal<Arguments...>::connect(T* object, void (T::*method)(Arguments...)) const
{
	return connect([object, method](Arguments... arguments) {
		(object->*method)(arguments...);
	});
}

template <typename... Arguments>
void Signal<Arguments...>::disconnectId(Connection::Id id) const
{
	_callbacks.erase(id);
}

} // namespace signalzeug
