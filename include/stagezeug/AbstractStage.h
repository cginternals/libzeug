#pragma once

#include <set>
#include <string>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>

namespace zeug 
{

class AbstractStageOutput;
class AbstractStageInput;

class STAGEZEUG_API AbstractStage
{
public:
    AbstractStage();
	virtual ~AbstractStage();

    bool execute();

    void setEnabled(bool enabled);
    bool isEnabled() const;

    const std::string & name() const;
    void setName(const std::string & name);

    bool dependsOn(const AbstractStage * stage) const;
public:
	Signal<> dependenciesChanged;

protected:
    void addOutput(AbstractStageOutput & output);
    void addInput(AbstractStageInput & input);

    bool needsToProcess() const;
    bool allInputsConnected() const;
    void validateOutputs();
    void validateInputs();

    virtual void process() = 0;

protected:
    bool m_enabled;
    std::string m_name;
    
    std::set<AbstractStageOutput*> m_outputs;
    std::set<AbstractStageInput*> m_inputs;
};

} // namespace zeug

