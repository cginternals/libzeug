#pragma once

#include <QString>
#include <QList>

#include <treeimportzeug/treeimportzeug.h>

namespace zeug
{
	
class Tree;
class TreeParserStrategy;

class TREEIMPORTZEUG_API TreeImport
{
public:
	static QList<Tree*> loadFromFile(const QString& filename);
	static QList<QString> registeredFileSuffixes();

	static void registerStrategy(TreeParserStrategy* strategy);
	static void registerStandardStrategies();
private:
	static QList<TreeParserStrategy*> s_strategies;
	TreeImport();
};

} // namespace zeug
