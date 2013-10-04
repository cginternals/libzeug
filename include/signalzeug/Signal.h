#pragma once

#include <functional>
#include <unordered_map>

#include <signalzeug/AbstractSignal.h>


namespace zeug
{

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
	mutable std::unordered_map<Connection::Id, Callback> m_callbacks;
};

} // namespace zeug
