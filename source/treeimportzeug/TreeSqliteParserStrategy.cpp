#include <treeimportzeug/TreeSqliteParserStrategy.h>

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace zeug
{

TreeSqliteParserStrategy::TreeSqliteParserStrategy()
{
}

void TreeSqliteParserStrategy::initialize(const QString& filename)
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

bool TreeSqliteParserStrategy::wantsToProcess()
{
	return m_database.open() && wantsToProcess(m_database);
}

QList<Tree*> TreeSqliteParserStrategy::process()
{
	createTrees();
	
	return m_trees;
}

void TreeSqliteParserStrategy::cleanup()
{
	clear();
	
	m_trees.clear();
	m_database.close();
}

QList<QVariantMap> TreeSqliteParserStrategy::executeQuery(const QString & statement) const
{
    QSqlQuery query(statement, m_database);
	
	if (query.exec())
	{
		QList<QVariantMap> rows;
		QSqlRecord record = query.record();
		QHash<QString, int> indices;

		for(int i = 0; i < record.count(); ++i)
			indices[record.fieldName(i)] = i;
		
		while (query.next())
		{
			QVariantMap row;

			for (const QString& fieldName : indices.keys())
				row[fieldName] = query.value(indices[fieldName]);
			
			rows << row;
		}		
		return rows;
	}
	else
	{
		qDebug() << query.executedQuery();
		qDebug() << "Error:" << query.lastError();
		
		return QList<QVariantMap>();
	}
}

} // namespace zeug
