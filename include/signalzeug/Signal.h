#pragma once

#include <functional>
#include <unordered_map>

#include <signalzeug/signalzeug.h>
#include <signalzeug/AbstractSignal.h>


namespace zeug
{

template <typename... Arguments>
class Signal : public AbstractSignal
{
public:
	typedef std::function<void(Arguments...)> Callback;

	Signal();

	void fire(Arguments... arguments);
	void operator()(Arguments... arguments);

	Connection connect(Callback callback) const;
	template <class T>
	Connection connect(T* object, void (T::*method)(Arguments...)) const;
	Connection connect(Signal& signal) const;

	void block();
	void unblock();

	Connection onFire(std::function<void()> callback) const;
protected:
	virtual void disconnectId(Connection::Id id) const override;

protected:
	mutable std::unordered_map<Connection::Id, Callback> m_callbacks;
	bool m_blocked;
};

} // namespace zeug

#include "Signal.hpp"
