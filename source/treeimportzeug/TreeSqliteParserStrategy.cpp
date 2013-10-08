
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <treeimportzeug/TreeSqliteParser.h>
#include <treeimportzeug/TreeSqliteParserStrategy.h>

namespace zeug
{

TreeSqliteParserStrategy::TreeSqliteParserStrategy(TreeSqliteParser & parser)
:   m_parser(parser)
{
}

QList<QVariantMap> TreeSqliteParserStrategy::executeQuery(const QString & statement) const
{
	QSqlQuery query(statement, m_parser.database());
	
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
