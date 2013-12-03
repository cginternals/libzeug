#pragma once

#include <QString>
#include <QSet>

#include <treeimportzeug/treeimportzeug.h>

namespace zeug
{

class Tree;

class TREEIMPORTZEUG_API TreeParserStrategy
{
public:
    virtual QSet<QString> wantedFileSuffixes() const = 0;
    virtual void initialize(const QString& filename) = 0;
    virtual bool wantsToProcess() = 0;
    virtual QList<Tree*> process() = 0;
    virtual void cleanup() = 0;
};

}
