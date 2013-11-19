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
    void processed();

    virtual bool isConnected() const = 0;

    bool isOptional() const;
    void setOptional(bool optional);

protected:
    void setOwner(AbstractStage * owner);

    void changed();

protected:
    AbstractStage * m_owner;
    bool m_hasChanged;
    bool m_optional;
};

template <typename T>
class STAGEZEUG_API StageInput
{
public:
    StageInput();

    const T & data() const;

    void connectTo(StageOutput<T> & output);
    virtual bool isConnected() const override;
protected:
    StageOutput<T>* m_output;
    ScopedConnection m_connection;
};

template <typename T>
StageInput<T>::StageInput()
: m_output(nullptr)
{
}

template <typename T>
bool StageInput<T>::isConnected() const
{
    return m_output != nullptr;
}

template <typename T>
const T & StageInput<T>::data() const
{
    return m_output->data();
}

template <typename T>
void StageInput<T>::connectTo(StageOutput<T> & output)
{
    if (output.owner()->dependsOn(this->owner()))
    {
        std::cout << "Circular dependency detected." << std::endl;
        return;
    }

    m_output = &output;

    m_connection = m_output->invalidated.connect([this]() {
        this->changed();
    });
    this->changed();
}

} // namespace zeug
