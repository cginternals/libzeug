#pragma once

#include <QHash>
#include <QString>

#include <treeimportzeug/treeimportzeug.h>
#include <treeimportzeug/TreeSqliteParserStrategy.h>


namespace zeug
{

class Tree;
class Node;

class TREEIMPORTZEUG_API SDStrategy : public TreeSqliteParserStrategy
{
public:
	SDStrategy();

	virtual QSet<QString> wantedFileSuffixes() const override;
protected:
	virtual void createTrees() override;
	virtual void clear() override;
	virtual bool wantsToProcess(QSqlDatabase& database) const override;
	
	void loadDirectories();
	void loadFiles();

	void insertNodesIntoTree();
	void insertIntoTree(Node * node);

	void addMetrics();
protected:
	QHash<int, Node*> m_nodes;
	QHash<int, int> m_parents;
	QHash<int, QString> m_metrics;

	Tree * m_tree;
};

} // namespace zeug
