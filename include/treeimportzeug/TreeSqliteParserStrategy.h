#pragma once

#include <QList>
#include <QString>
#include <QVariantMap>


namespace zeug
{

class TreeSqliteParser;

class TREEIMPORTZEUG_API TreeSqliteParserStrategy
{
public:
	TreeSqliteParserStrategy(TreeSqliteParser & parser);

	virtual void processOne() = 0;
	virtual void processMultiple() = 0;

protected:
    QList<QVariantMap> executeQuery(const QString & statement) const;

protected:
	TreeSqliteParser & m_parser;
};

} // namespace zeug
