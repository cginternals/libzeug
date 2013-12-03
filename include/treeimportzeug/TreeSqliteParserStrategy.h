#pragma once

#include <QList>
#include <QSet>
#include <QString>
#include <QVariantMap>
#include <QSqlDatabase>

#include <treeimportzeug/treeimportzeug.h>

#include <treeimportzeug/TreeParserStrategy.h>

namespace zeug
{

class Tree;

class TREEIMPORTZEUG_API TreeSqliteParserStrategy : public TreeParserStrategy
{
public:
	TreeSqliteParserStrategy();
	
	virtual void initialize(const QString& filename) override;
	virtual bool wantsToProcess() override;
	virtual QList<Tree*> process() override;
	virtual void cleanup() override;
protected:
	QList<QVariantMap> executeQuery(const QString & statement) const;
	QSqlDatabase m_database;
	QList<Tree*> m_trees;
	
	virtual void createTrees() = 0;
	virtual void clear() = 0;
	virtual bool wantsToProcess(QSqlDatabase& database) const = 0;
};

} // namespace zeug
