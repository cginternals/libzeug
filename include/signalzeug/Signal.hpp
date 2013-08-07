#pragma once

#include <AbstractSignal.h>

#include <functional>
#include <unordered_map>

template <typename... Arguments>
class SIGNALZEUG_API Signal : public AbstractSignal
{
public:
	typedef std::function<void(Arguments...)> Callback;

	Signal();

	void fire(Arguments... arguments);

	ConnectionHandle connect(Callback callback) const;
	template <class T>
	ConnectionHandle connect(T* object, void (T::*method)(Arguments...)) const;
protected:
	void disconnect(HandleId id) const override;
protected:
	mutable std::unordered_map<HandleId, Callback> _callbacks;
};


template <typename... Arguments>
Signal<Arguments...>::Signal()
{
}

template <typename... Arguments>
void Signal<Arguments...>::fire(Arguments... arguments)
{
	for (const std::pair<HandleId, Callback>& pair: _callbacks)
	{
		Callback callback = pair.second;
		callback(arguments...);
	}
}

template <typename... Arguments>
ConnectionHandle Signal<Arguments...>::connect(Callback callback) const
{
	ConnectionHandle handle = createConnectionHandle();
	_callbacks[handle.id()] = callback;
	return handle;
}

template <typename... Arguments>
template <class T>
ConnectionHandle Signal<Arguments...>::connect(T* object, void (T::*method)(Arguments...)) const
{
	return connect([&object, &method](Arguments... arguments) {
		(object->*method)(arguments...);
	});
}

template <typename... Arguments>
void Signal<Arguments...>::disconnect(HandleId id) const
{
	_callbacks.erase(id);
}
