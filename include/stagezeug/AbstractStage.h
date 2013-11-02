#pragma once

#include <set>
#include <string>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>

namespace zeug 
{

class StageData;

class STAGEZEUG_API AbstractStage
{
public:
    AbstractStage(StageData * output);
	virtual ~AbstractStage();

    const StageData * output() const;

    bool execute();

    void require(AbstractStage * stage);

    void setEnabled(bool enabled);
    bool isEnabled() const;

    const std::string & name() const;
    void setName(const std::string & name);

    bool dependsOn(const AbstractStage * stage) const;

	template <typename T, typename... Args>
    void requireAll(T * stage, Args... rest);

public:
	Signal<> dependenciesChanged;

protected:
    void requireAll();

    void addInput(const StageData * input);
    void invalidateOutput();

    virtual void inputAdded(const StageData * input);

    virtual void process() = 0;

protected:
    bool m_enabled;
    std::string m_name;
    
    StageData * m_output;
    std::set<const StageData*> m_inputs;
};

} // namespace zeug

#include "AbstractStage.hpp"
