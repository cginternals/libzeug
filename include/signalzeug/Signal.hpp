#pragma once

namespace zeug 
{

template <typename... Arguments>
Signal<Arguments...>::Signal()
{
}

template <typename... Arguments>
void Signal<Arguments...>::fire(Arguments... arguments)
{
	for (auto & pair : m_callbacks)
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
	m_callbacks[connection.id()] = callback;
	return connection;
}

template <typename... Arguments>
template <class T>
Connection Signal<Arguments...>::connect(T * object, void (T::*method)(Arguments...)) const
{
	return connect([object, method](Arguments... arguments) 
    {
		(object->*method)(arguments...);
	});
}

template <typename... Arguments>
void Signal<Arguments...>::disconnectId(Connection::Id id) const
{
	m_callbacks.erase(id);
}

} // namespace zeug
