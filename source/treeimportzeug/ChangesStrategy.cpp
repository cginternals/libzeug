#include <ChangesStrategy.h>

#include <TreeSqliteParser.h>

#include <QHash>

ChangesStrategy::ChangesStrategy(TreeSqliteParser& parser)
: TreeSqliteParserStrategy(parser)
, _nextId(0)
{
}

void ChangesStrategy::processOne()
{
	processRevisions(executeQuery("SELECT id FROM revisions WHERE 1 ORDER BY id LIMIT 1"));
}

void ChangesStrategy::processMultiple()
{
	processRevisions(executeQuery("SELECT id FROM revisions WHERE 1 ORDER BY id"));
}

void ChangesStrategy::processRevisions(const QList<QVariantMap>& revisions)
{
	for (const QVariantMap& revision : revisions)
	{
		createTreeForRevision(revision["id"].toUInt());
	}
	
	transferTrees();
}

void ChangesStrategy::createTreeForRevision(unsigned revisionId)
{
	Tree* tree = new Tree();
	
	_trees << tree;
	
	QHash<int, Node*> nodes;
	QHash<int, int> parentIds;
	QHash<int, long> hashes;
	
	QList<QVariantMap> rows = executeQuery("SELECT id, hash, type_id, parent_id FROM nodes WHERE revision_id = " + QString::number(revisionId) + " ORDER BY id");
	for (const QVariantMap& node : rows)
	{
		int id = idFor(node["hash"].toInt());
		nodes[id] = new Node(id);
		
		hashes[node["id"].toInt()] = node["hash"].toInt();
	}
	
	for (const QVariantMap& node : rows)
	{
		parentIds[idFor(node["hash"].toInt())] = idFor(hashes[node["parent_id"].toInt()]);
	}
	
	for (Node* node : nodes)
	{
		insertIntoTree(node, tree, nodes, parentIds);
	}
}

void ChangesStrategy::insertIntoTree(Node* node, Tree* tree, const QHash<int, Node*>& nodes, const QHash<int, int>& parentIds) const
{
	if (tree->getNode(node->id()))
	{
		return;
	}
	
	if (parentIds.value(node->id(), 0) <= 0)
	{
		tree->root()->addChild(node);
		
		return;
	}
	
	if (!tree->getNode(parentIds.value(node->id(), 0)))
	{
		insertIntoTree(nodes.value(parentIds.value(node->id(), 0), nullptr), tree, nodes, parentIds);
	}
	
	tree->getNode(parentIds.value(node->id(), 0))->addChild(node);
}

void ChangesStrategy::transferTrees()
{
	_parser.trees() = _trees;
}

int ChangesStrategy::idFor(long hash) const
{
	if (!_ids.contains(hash))
	{
		_ids[hash] = _nextId;
		
		++_nextId;
	}
	
	return _ids[hash];
}
