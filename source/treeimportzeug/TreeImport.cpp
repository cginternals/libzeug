#include <treeimportzeug/TreeImport.h>

#include <treeimportzeug/TreeParserStrategy.h>

#include <treeimportzeug/ChangesStrategy.h>
#include <treeimportzeug/CityGMLStrategy.h>
#include <treeimportzeug/RepositoryStrategy.h>
#include <treeimportzeug/SoftwareSystemStrategy.h>
#include <treeimportzeug/TreeStrategy.h>

#include <QFileInfo>
#include <QDebug>

namespace zeug
{

QList<TreeParserStrategy*> TreeImport::s_strategies;

QList<QString> TreeImport::registeredFileSuffixes()
{
    QSet<QString> suffixes;

    for (TreeParserStrategy* strategy : s_strategies)
    {
        suffixes |= strategy->wantedFileSuffixes();
    }

    return suffixes.toList();
}

void TreeImport::registerStrategy(TreeParserStrategy* strategy)
{
    s_strategies << strategy;
}

void TreeImport::registerStandardStrategies()
{
	registerStrategy(new ChangesStrategy());
	registerStrategy(new CityGMLStrategy());
	registerStrategy(new SoftwareSystemStrategy());
	registerStrategy(new TreeStrategy());
    registerStrategy(new RepositoryStrategy());
}

QList<Tree*> TreeImport::loadFromFile(const QString& filename)
{
    QList<TreeParserStrategy*> potentialStrategies;
    for (TreeParserStrategy* strategy : s_strategies)
    {
        if (strategy->wantedFileSuffixes().contains("*") || strategy->wantedFileSuffixes().contains(QFileInfo(filename).suffix()))
        {
            potentialStrategies << strategy;
        }
    }

    QList<TreeParserStrategy*> possibleStrategies;
    for (TreeParserStrategy* strategy : potentialStrategies)
    {
        strategy->initialize(filename);

        if (strategy->wantsToProcess())
        {
            possibleStrategies << strategy;
        }
    }

    TreeParserStrategy* chosenStrategy = possibleStrategies.size() >= 1 ? possibleStrategies.front() : nullptr;

    if (possibleStrategies.size() > 1)
    {
        qWarning() << possibleStrategies.size() << "strategies registered to handle" << filename << "so the first one is chosen.";
    }

    QList<zeug::Tree*> trees;
    if (chosenStrategy)
    {
        trees = chosenStrategy->process();
    }
    else
    {
        qWarning() << "No strategy registered to handle" << filename;
    }

    for (TreeParserStrategy* strategy : potentialStrategies)
    {
        strategy->cleanup();
    }

	return trees;
}

} // namespace zeug
