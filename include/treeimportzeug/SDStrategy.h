#pragma once

#include <TreeSqliteParserStrategy.h>

#include <Tree.h>

#include <QHash>
#include <QString>
#include <QVariantMap>

class SDStrategy : public TreeSqliteParserStrategy
{
public:
	SDStrategy(TreeSqliteParser& parser);
	
	virtual void process();
protected:
	QHash<int, Node*> _nodes;
	QHash<int, int> _parents;
	QHash<int, QString> _metrics;
	
	void loadDirectories();
	void loadFiles();
	void insertNodesIntoTree();
	void insertIntoTree(Node* node);
	void addMetrics();
private:
	QList<QVariantMap> executeQuery(const QString& statement) const;
};
