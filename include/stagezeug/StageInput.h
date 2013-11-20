#pragma once

#include <set>
#include <string>
#include <iostream>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>
#include <signalzeug/ScopedConnection.h>

namespace zeug
{

class AbstractStage;
template <typename T> class StageOutput;

class STAGEZEUG_API AbstractStageInput
{
    friend class AbstractStage;

public:
    AbstractStageInput();
    virtual ~AbstractStageInput();

    const AbstractStage * owner() const;

    bool hasChanged() const;

    void changed();
    void processed();

    virtual bool isUsable() const = 0;

    bool isOptional() const;
    void setOptional(bool optional);

protected:
    void setOwner(AbstractStage * owner);

    void requireStage(const AbstractStage * stage);
protected:
    AbstractStage * m_owner;
    bool m_hasChanged;
    bool m_optional;
};

template <typename T>
class STAGEZEUG_API StageInputSlot : public AbstractStageInput
{
public:
    StageInputSlot();

    const T & data() const;

    void connectTo(StageOutput<T> & output);
    StageOutput<T> & operator=(StageOutput<T> & output);

    virtual bool isUsable() const override;
protected:
    StageOutput<T>* m_output;
    ScopedConnection m_connection;
};

template <typename T>
class STAGEZEUG_API StageInput : public AbstractStageInput
{
public:
    StageInput();

    T & data();
    const T & data() const;

    //const T & operator=(const T & value);

    virtual bool isUsable() const override;
protected:
    T m_data;
};

template <typename T>
StageInputSlot<T>::StageInputSlot()
: m_output(nullptr)
{
}

template <typename T>
bool StageInputSlot<T>::isUsable() const
{
    return m_output != nullptr;
}

template <typename T>
const T & StageInputSlot<T>::data() const
{
    return m_output->data();
}

template <typename T>
StageOutput<T> & StageInputSlot<T>::operator=(StageOutput<T> & output)
{
    connectTo(output);
    return output;
}

template <typename T>
void StageInputSlot<T>::connectTo(StageOutput<T> & output)
{
    if (!this->owner())
        return;

    if (output.owner() && output.owner()->requires(this->owner()))
    {
        std::cout << "Circular dependency detected." << std::endl;
        return;
    }

    m_output = &output;

    requireStage(output.owner());

    m_connection = m_output->invalidated.connect([this]() {
        this->changed();
    });
    this->changed();
}


template <typename T>
StageInput<T>::StageInput()
: m_data()
{
    changed();
}

template <typename T>
bool StageInput<T>::isUsable() const
{
    return true;
}

template <typename T>
T & StageInput<T>::data()
{
    return m_data;
}

template <typename T>
const T & StageInput<T>::data() const
{
    return m_data;
}

} // namespace zeug
