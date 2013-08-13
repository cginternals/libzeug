#include <TreeSqliteParser.h>

#include <SDStrategy.h>

#include <QDebug>

TreeSqliteParser::TreeSqliteParser(const QString& filename)
: _tree(nullptr)
, _strategy(nullptr)
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
		parser._tree = new Tree();
		parser._strategy = new SDStrategy(parser);
		
		parser._strategy->process();
	}
	else
	{
		qDebug() << "Couldn't open database";
		
		return nullptr;
	}
	
	return parser.tree();
}

Tree* TreeSqliteParser::tree()
{
	return _tree;
}

QSqlDatabase& TreeSqliteParser::database()
{
	return _database;
}
