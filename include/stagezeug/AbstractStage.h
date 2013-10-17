#pragma once

#include <set>
#include <string>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>

namespace zeug {

class STAGEZEUG_API AbstractStage;

class STAGEZEUG_API StageData
{
	friend class AbstractStage;
public:
    StageData();
    virtual ~StageData();

    const AbstractStage* owner() const;

    bool isValid() const;
    void invalidate();
    void setToValid();
public:
    Signal<> invalidated;
protected:
    AbstractStage* _owner;
    bool _valid;
private:
	void setOwner(AbstractStage* owner);
};

class STAGEZEUG_API AbstractStage
{
public:
    AbstractStage(StageData* output);
	virtual ~AbstractStage();

    const StageData* output() const;

    bool execute();

    void requireInput(StageData* input);

    void setEnabled(bool enabled);
    bool isEnabled() const;

    const std::string& name() const;
    void setName(const std::string& name);

    bool dependsOn(const AbstractStage* stage) const;
public:
	Signal<> dependenciesChanged;
protected:
    bool _enabled;
    std::string _name;
    StageData* _output;
    std::set<StageData*> _inputs;

	void invalidateOutput();
    virtual void inputAdded(StageData* input);

	virtual void process() = 0;
};


} // namespace zeug
