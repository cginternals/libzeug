#include <TreeSqliteParser.h>

#include <SDStrategy.h>

#include <QDebug>

TreeSqliteParser::TreeSqliteParser(const QString& filename)
: _strategy(nullptr)
{
	if (QSqlDatabase::contains(filename))
	{
		_database = QSqlDatabase::database(filename);
	}
	else
	{
		_database = QSqlDatabase::addDatabase("QSQLITE", filename);
		
		_database.setDatabaseName(filename);
	}
}

Tree* TreeSqliteParser::createTreeFromDatabase(const QString& filename)
{
	TreeSqliteParser parser(filename);
	
	if (parser.database().open())
	{
		parser._strategy = new SDStrategy(parser);
		
		parser._strategy->processOne();
	}
	else
	{
		qDebug() << "Couldn't open database";
		
		return nullptr;
	}
	
	return parser.tree();
}

QList<Tree*> TreeSqliteParser::createTreesFromDatabase(const QString& filename)
{
	TreeSqliteParser parser(filename);
	
	if (parser.database().open())
	{
		parser._strategy = new SDStrategy(parser);
		
		parser._strategy->processMultiple();
	}
	else
	{
		qDebug() << "Couldn't open database";
		
		return QList<Tree*>();
	}
	
	return parser.trees();
}

Tree* TreeSqliteParser::tree()
{
	return _trees.first();
}

QList<Tree*>& TreeSqliteParser::trees()
{
	return _trees;
}

QSqlDatabase& TreeSqliteParser::database()
{
	return _database;
}
