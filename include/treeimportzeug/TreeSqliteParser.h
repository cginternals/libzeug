#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QList>

#include <treezeug/Tree.h>

class TreeSqliteParserStrategy;

class TreeSqliteParser
{
public:
	TreeSqliteParser(const QString& filename);
	
	static Tree* createTreeFromDatabase(const QString& filename);
	static QList<Tree*> createTreesFromDatabase(const QString& filename);
	
	Tree* tree();
	QList<Tree*>& trees();
	QSqlDatabase& database();
protected:
	QList<Tree*> _trees;
	TreeSqliteParserStrategy* m_strategy;
	QSqlDatabase _database;
};
