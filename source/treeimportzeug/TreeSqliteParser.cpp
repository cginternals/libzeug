
#include <QDebug>
#include <QSqlRecord>


#include <treeimportzeug/SDStrategy.h>
#include <treeimportzeug/ChangesStrategy.h>

#include <treeimportzeug/TreeSqliteParser.h>


namespace zeug
{

TreeSqliteParser::TreeSqliteParser(const QString & filename)
:   m_strategy(nullptr)
{
	if (QSqlDatabase::contains(filename))
	{
		m_database = QSqlDatabase::database(filename);
	}
	else
	{
		m_database = QSqlDatabase::addDatabase("QSQLITE", filename);		
		m_database.setDatabaseName(filename);
	}
}

Tree * TreeSqliteParser::createTreeFromDatabase(const QString & filename)
{
	TreeSqliteParser parser(filename);
	
	if (parser.database().open())
	{
		if (parser.database().record("nodes").isEmpty())
			parser.m_strategy = new SDStrategy(parser);
		else
			parser.m_strategy = new ChangesStrategy(parser);
		
		parser.m_strategy->processOne();
	}
	else
	{
		qDebug() << "Couldn't open database";		
		return nullptr;
	}
	return parser.tree();
}

QList<Tree*> TreeSqliteParser::createTreesFromDatabase(const QString & filename)
{
	TreeSqliteParser parser(filename);
	
	if (parser.database().open())
	{
		if (parser.database().record("nodes").isEmpty())
			parser.m_strategy = new SDStrategy(parser);
		else
			parser.m_strategy = new ChangesStrategy(parser);

		parser.m_strategy->processMultiple();
	}
	else
	{
		qDebug() << "Couldn't open database";		
		return QList<Tree*>();
	}

	return parser.trees();
}

Tree * TreeSqliteParser::tree()
{
	return m_trees.first();
}

QList<Tree*> & TreeSqliteParser::trees()
{
	return m_trees;
}

QSqlDatabase & TreeSqliteParser::database()
{
	return m_database;
}

} // namespace zeug
