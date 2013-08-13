#pragma once

#include <TreeSqliteParserStrategy.h>

#include <Tree.h>

#include <QList>

class ChangesStrategy : public TreeSqliteParserStrategy
{
public:
	ChangesStrategy(TreeSqliteParser& parser);
	
	virtual void processOne();
	virtual void processMultiple();
protected:
	QList<Tree*> _trees;
	mutable QHash<long, int> _ids;
	mutable int _nextId;
	
	void createTreeForRevision(unsigned revisionId);
	void transferTrees();
	int idFor(long hash) const;
	void insertIntoTree(Node* node, Tree* tree, const QHash<int, Node*>& nodes, const QHash<int, int>& parentIds) const;
};
