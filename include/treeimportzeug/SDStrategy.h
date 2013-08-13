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
	
	virtual void processOne();
	virtual void processMultiple();
protected:
	QHash<int, Node*> _nodes;
	QHash<int, int> _parents;
	QHash<int, QString> _metrics;
	Tree* _tree;
	QList<Tree*> _trees;
	
	void loadDirectories();
	void loadFiles();
	void insertNodesIntoTree();
	void insertIntoTree(Node* node);
	void addMetricsForOneTimestamp();
	void addMetricsForAllTimestamps();
	void transferTrees();
private:
	QList<QVariantMap> executeQuery(const QString& statement) const;
};
