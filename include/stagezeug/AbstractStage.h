#pragma once

#include <set>
#include <string>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>

namespace zeug {

class STAGEZEUG_API AbstractStage
{
public:
    enum ExecutionPolicy
    {
        WhenInvalid,
        Always,
        Never
    };

    AbstractStage(ExecutionPolicy policy = WhenInvalid);
	virtual ~AbstractStage();

    bool execute();

    void invalidate();
    bool isValid() const;

	template<typename T, typename... Args>
    void require(T* stage, Args... stages);
    bool requires(const AbstractStage* stage) const;

    void setEnabled(bool enabled);
    bool isEnabled() const;

    void setExecutionPolicy(ExecutionPolicy policy);
    ExecutionPolicy policy() const;

    const std::string& name() const;
    void setName(const std::string& name);
public:
	Signal<> dependenciesChanged;
protected:
    ExecutionPolicy _policy;
    bool _enabled;
    bool _valid;
    std::string _name;

	std::set<AbstractStage*> _requiredStages;
    std::set<AbstractStage*> _dependentStages;

	void require() {}
	void addRequiredStage(AbstractStage* stage);
	void addDependentStage(AbstractStage* stage);

	virtual void invalidated();
    bool needsToExecute() const;

	virtual void process() = 0;
};

template<typename T, typename... Args>
void AbstractStage::require(T* stage, Args... stages)
{
    addRequiredStage(stage);
    require(stages...);
}

} // namespace zeug
