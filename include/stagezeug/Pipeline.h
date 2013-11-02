#pragma once

#include <vector>

#include <stagezeug/stagezeug.h>
#include <stagezeug/AbstractStage.h>

namespace zeug 
{

class STAGEZEUG_API Pipeline
{
public:
    Pipeline();
    virtual ~Pipeline();

    virtual void execute();

    virtual void addStage(AbstractStage * stage);

    template<typename T, typename... Args>
    void addStages(T stage, Args... stages);

	const std::vector<AbstractStage*> & stages() const;


protected:
    void sortDependencies();
    void addStages();

protected:
    std::vector<AbstractStage*> m_stages;
    bool m_dependenciesSorted;
};

} // namespace zeug

#include "Pipeline.hpp"