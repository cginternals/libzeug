#pragma once

#include <set>
#include <string>

#include <stagezeug/stagezeug.h>
#include <signalzeug/Signal.h>

namespace zeug 
{

class AbstractStage;

class STAGEZEUG_API StageData
{
	friend class AbstractStage;

public:
    StageData();
    virtual ~StageData();

    const AbstractStage * owner() const;

    bool isValid() const;
    void invalidate();
    void setToValid();

public:
    Signal<> invalidated;

private:
	void setOwner(AbstractStage * owner);

protected:
    AbstractStage * m_owner;
    mutable bool m_valid;

};

} // namespace zeug
