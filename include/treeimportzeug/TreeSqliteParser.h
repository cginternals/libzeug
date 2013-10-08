#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QList>

#include <treezeug/Tree.h>

#include <treeimportzeug/treeimportzeug.h>


namespace zeug
{

class TreeSqliteParserStrategy;

class TREEIMPORTZEUG_API TreeSqliteParser
{
public:
	TreeSqliteParser(const QString & filename);
	
	static Tree* createTreeFromDatabase(const QString & filename);
	static QList<Tree*> createTreesFromDatabase(const QString & filename);
	
	Tree * tree();
	QList<Tree*> & trees();
	QSqlDatabase & database();

protected:
	QList<Tree*> m_trees;
	TreeSqliteParserStrategy * m_strategy;

	QSqlDatabase m_database;
};

} // namespace zeug
