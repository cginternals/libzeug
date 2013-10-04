#pragma once

#include <treeimportzeug/TreeSqliteParserStrategy.h>

#include <treezeug/Tree.h>

#include <QHash>
#include <QString>

class SDStrategy : public TreeSqliteParserStrategy
{
public:
	SDStrategy(TreeSqliteParser& parser);
	
	virtual void processOne();
	virtual void processMultiple();
protected:
	QHash<int, Node*> m_nodes;
	QHash<int, int> _parents;
	QHash<int, QString> _metrics;
	Tree* m_tree;
	QList<Tree*> _trees;
	
	void loadDirectories();
	void loadFiles();
	void insertNodesIntoTree();
	void insertIntoTree(Node* node);
	void addMetricsForOneTimestamp();
	void addMetricsForAllTimestamps();
	void transferTrees();
};
