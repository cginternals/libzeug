#pragma once

#include <set>
#include <string>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>

namespace zeug 
{

class AbstractStage;

class STAGEZEUG_API AbstractStageOutput
{
	friend class AbstractStage;

public:
    AbstractStageOutput();
    virtual ~AbstractStageOutput();

    const AbstractStage * owner() const;

    void invalidate();

public:
    Signal<> invalidated;

protected:
	void setOwner(AbstractStage * owner);

protected:
    AbstractStage * m_owner;
};

template <typename T>
class STAGEZEUG_API StageOutput : public AbstractStageOutput
{
public:
    StageOutput();

    T & data();
    const T & data() const;
protected:
    T m_data;
};

template <typename T>
StageOutput<T>::StageOutput()
{
}

template <typename T>
T & StageOutput<T>::data()
{
    return m_data;
}

template <typename T>
const T & StageOutput<T>::data() const
{
    return m_data;
}

} // namespace zeug
