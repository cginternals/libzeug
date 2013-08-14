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
	loadAttributes();
	processRevisions(executeQuery("SELECT id FROM revisions WHERE 1 ORDER BY id LIMIT 1"));
}

void ChangesStrategy::processMultiple()
{
	loadAttributes();
	processRevisions(executeQuery("SELECT id FROM revisions WHERE 1 ORDER BY id"));
}

void ChangesStrategy::loadAttributes()
{
	for (const QVariantMap& attributeType : executeQuery("SELECT id, type_id, name, type FROM schema_attrs WHERE 1"))
	{
		_attributes[NodeType(attributeType["type_id"].toInt())] << Attribute(
			attributeType["name"].toString(),
			attributeType["type"].toString() == "TEXT" ? AT_Text : AT_Integer,
			attributeType["id"].toUInt()
		);
		
		_attributeValues[attributeType["id"].toUInt()] = executeQuery("SELECT node_id, value FROM attr_" + QString::number(attributeType["id"].toUInt()));
	}
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
	
	tree->addAttributeMap("id", AttributeMap::Numeric);
	tree->addAttributeMap("depth", AttributeMap::Numeric);
	
	for (const QList<Attribute>& attributes : _attributes)
	{
		for (const Attribute& attribute : attributes)
		{
			if (attribute.name == "label")
			{
				continue;
			}
			
			tree->addAttributeMap(
				attribute.name.toStdString(),
				attribute.type == AT_Integer ? AttributeMap::Numeric : AttributeMap::Nominal
			);
		}
	}
	
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
	
	for (Node* node : nodes)
	{
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	}
	
	for (const QList<Attribute>& attributeList : _attributes)
	{
		for (const Attribute& attribute : attributeList)
		{
			for (const QVariantMap& attributeValue : _attributeValues[attribute.index])
			{
				if (!hashes.contains(attributeValue["node_id"].toInt()))
				{
					continue;
				}
				
				Node* node = tree->getNode(idFor(hashes[attributeValue["node_id"].toInt()]));
				
				Q_ASSERT(node != nullptr);
				
				if (attribute.name == "label")
				{
					node->setName(attributeValue["value"].toString().toStdString());
				}
				else
				{
					node->setAttribute(attribute.name.toStdString(), attributeValue["value"].toString().toStdString());
				}
			}
		}
	}
}

void ChangesStrategy::insertIntoTree(Node* node, Tree* tree, const QHash<int, Node*>& nodes, const QHash<int, int>& parentIds) const
{
	if (node->id() == 0)
	{
		tree->setRoot(node);
		
		return;
	}
	
	if (tree->getNode(node->id()))
	{
		Q_ASSERT(tree->getNode(node->id()) == node);
		
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
	
	Q_ASSERT(node->tree() == tree);
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
