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
    friend class AbstractStageInput;
public:
    AbstractStage();
	virtual ~AbstractStage();

    bool execute();

    void setEnabled(bool enabled);
    bool isEnabled() const;

    const std::string & name() const;
    void setName(const std::string & name);

    bool requires(const AbstractStage * stage) const;
public:
	Signal<> dependenciesChanged;

protected:
    void addOutput(AbstractStageOutput & output);
    void addInput(AbstractStageInput & input);

    void require(const AbstractStage * stage);

    bool needsToProcess() const;
    bool inputsUsable() const;
    void markInputsProcessed();

    virtual void process() = 0;

protected:
    bool m_enabled;
    std::string m_name;

    std::set<const AbstractStage*> m_required;
    
    std::set<AbstractStageOutput*> m_outputs;
    std::set<AbstractStageInput*> m_inputs;
};

} // namespace zeug

