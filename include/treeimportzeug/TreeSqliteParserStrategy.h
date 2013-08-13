#pragma once

#include <QList>
#include <QString>
#include <QVariantMap>

class TreeSqliteParser;

class TreeSqliteParserStrategy
{
public:
	TreeSqliteParserStrategy(TreeSqliteParser& parser);
	
	virtual void processOne() = 0;
	virtual void processMultiple() = 0;
protected:
	TreeSqliteParser& _parser;
	
	QList<QVariantMap> executeQuery(const QString& statement) const;
};
