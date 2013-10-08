#pragma once

#include <QHash>
#include <QString>

#include <treezeug/Tree.h>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeSqliteParserStrategy.h>


namespace zeug
{

class TREEIMPORTZEUG_API SDStrategy : public TreeSqliteParserStrategy
{
public:
	SDStrategy(TreeSqliteParser & parser);
	
	virtual void processOne();
	virtual void processMultiple();

protected:
    void loadDirectories();
	void loadFiles();
	
    void insertNodesIntoTree();
	void insertIntoTree(Node * node);
	
    void addMetricsForOneTimestamp();
	void addMetricsForAllTimestamps();
	
    void transferTrees();

protected:
	QHash<int, Node*> m_nodes;
	QHash<int, int> m_parents;
	QHash<int, QString> m_metrics;

    Tree * m_tree;
	QList<Tree*> m_trees;
};

} // namespace zeug
