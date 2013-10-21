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
    mutable bool _valid;
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

    void require(AbstractStage* stage);

    void setEnabled(bool enabled);
    bool isEnabled() const;

    const std::string& name() const;
    void setName(const std::string& name);

    bool dependsOn(const AbstractStage* stage) const;

	template <typename T, typename... Args>
	void requireAll(T* stage, Args... rest)
	{
		require(stage);
		requireAll(rest...);
	}
public:
	Signal<> dependenciesChanged;
protected:
    bool _enabled;
    std::string _name;
    StageData* _output;
    std::set<const StageData*> _inputs;

	void requireAll() {}

	void addInput(const StageData* input);
	virtual void inputAdded(const StageData* input);
	void invalidateOutput();

	virtual void process() = 0;
};


} // namespace zeug
