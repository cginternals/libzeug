#include <treeimportzeug/SDStrategy.h>

#include <treeimportzeug/TreeSqliteParser.h>

#include <QDateTime>

SDStrategy::SDStrategy(TreeSqliteParser& parser)
: TreeSqliteParserStrategy(parser)
, _tree(new Tree(""))
{
}

void SDStrategy::processOne()
{
	loadDirectories();
	loadFiles();
	insertNodesIntoTree();
	addMetricsForOneTimestamp();
	transferTrees();
}

void SDStrategy::processMultiple()
{
	loadDirectories();
	loadFiles();
	insertNodesIntoTree();
	addMetricsForAllTimestamps();
	transferTrees();
}

void SDStrategy::loadDirectories()
{
	for (const QVariantMap& directory : executeQuery("SELECT id, parent, name FROM directories WHERE 1 ORDER BY id"))
	{
		Node* node = new Node(directory["id"].toInt());
		node->setName(directory["name"].toString().toStdString());
		
		_nodes[directory["id"].toInt()] = node;
		_parents[directory["id"].toInt()] = directory["parent"].toInt();
	}
}

void SDStrategy::loadFiles()
{
	for (const QVariantMap& file : executeQuery("SELECT id, directory, name FROM items WHERE 1 ORDER BY id"))
	{
		Node* node = new Node(file["id"].toInt());
		node->setName(file["name"].toString().toStdString());
		
		_nodes[file["id"].toInt()] = node;
		_parents[file["id"].toInt()] = file["directory"].toInt();
	}
}

void SDStrategy::insertNodesIntoTree()
{
	for (Node* node : _nodes)
	{
		insertIntoTree(node);
	}
}

void SDStrategy::insertIntoTree(Node* node)
{
	if (_tree->getNode(node->id()))
	{
		return;
	}
	
	if (!_tree->getNode(_parents.value(node->id())))
	{
		insertIntoTree(_nodes.value(_parents.value(node->id())));
	}
	
	_tree->getNode(_parents.value(node->id()))->addChild(node);
}

void SDStrategy::addMetricsForOneTimestamp()
{
	_tree->addAttributeMap("id", AttributeMap::Numeric);
	_tree->addAttributeMap("depth", AttributeMap::Numeric);
	
	_tree->nodesDo([](Node* node) {
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	});
	
	for (const QVariantMap& metricMeta : executeQuery("SELECT id, name, type FROM metricsmeta WHERE 1 ORDER BY id"))
	{
		_tree->addAttributeMap(
			metricMeta["name"].toString().toStdString(),
			metricMeta["type"].toInt() == 1 ? AttributeMap::Numeric : AttributeMap::Nominal
		);
		
		_metrics[metricMeta["id"].toInt()] = metricMeta["name"].toString();
	}
	
	for (const QVariantMap& metricSet : executeQuery("SELECT timestamp FROM metricssets WHERE 1 ORDER BY timestamp LIMIT 1"))
	{
        QDateTime time;
        time.setMSecsSinceEpoch(metricSet["timestamp"].toULongLong());

        _tree->setName(time.toString("dd.MM.yyyy hh:mm").toStdString());

		for (const QVariantMap& metricData : executeQuery("SELECT itemId, metricId, value FROM metricsdata WHERE timestamp = " + metricSet["timestamp"].toString() + " ORDER BY itemId"))
		{
			_tree->getNode(metricData["itemId"].toInt())->setAttribute(
				_metrics[metricData["metricId"].toInt()].toStdString(),
				metricData["value"].toString().toStdString()
			);
		}
		
		_trees << _tree;
		
		return;
	}
}

void SDStrategy::addMetricsForAllTimestamps()
{
	_tree->addAttributeMap("id", AttributeMap::Numeric);
	_tree->addAttributeMap("depth", AttributeMap::Numeric);
	
	_tree->nodesDo([](Node* node) {
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	});
	
	for (const QVariantMap& metricMeta : executeQuery("SELECT id, name, type FROM metricsmeta WHERE 1 ORDER BY id"))
	{
		_tree->addAttributeMap(
			metricMeta["name"].toString().toStdString(),
			metricMeta["type"].toInt() == 1 ? AttributeMap::Numeric : AttributeMap::Nominal
		);
		
		_metrics[metricMeta["id"].toInt()] = metricMeta["name"].toString();
	}
	
	for (const QVariantMap& metricSet : executeQuery("SELECT timestamp FROM metricssets WHERE 1 ORDER BY timestamp"))
	{
		Tree* tree = _tree->copy();

        QDateTime time;
        time.setMSecsSinceEpoch(metricSet["timestamp"].toULongLong());

        _tree->setName(time.toString("dd.MM.yyyy hh:mm").toStdString());
		
		for (const QVariantMap& metricData : executeQuery("SELECT itemId, metricId, value FROM metricsdata WHERE timestamp = " + metricSet["timestamp"].toString() + " ORDER BY itemId"))
		{
			tree->getNode(metricData["itemId"].toInt())->setAttribute(
				_metrics[metricData["metricId"].toInt()].toStdString(),
				metricData["value"].toString().toStdString()
			);
		}
		
		_trees << tree;
	}
	
	delete _tree;
}

void SDStrategy::transferTrees()
{
	_parser.trees() = _trees;
}
