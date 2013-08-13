#pragma once

#include <QString>
#include <QSqlDatabase>

#include <Tree.h>

class TreeSqliteParserStrategy;

class TreeSqliteParser
{
public:
	TreeSqliteParser(const QString& filename);
	
	static Tree* createTreeFromDatabase(const QString& filename);
	
	Tree* tree();
	QSqlDatabase& database();
protected:
	Tree* _tree;
	TreeSqliteParserStrategy* _strategy;
	QSqlDatabase _database;
};
