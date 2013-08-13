#include <SDStrategy.h>

#include <TreeSqliteParser.h>

#include <QHash>
#include <QVariantMap>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

SDStrategy::SDStrategy(TreeSqliteParser& parser)
: TreeSqliteParserStrategy(parser)
{
}

void SDStrategy::process()
{
	loadDirectories();
	loadFiles();
	insertNodesIntoTree();
	addMetrics();
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
	if (_parser.tree()->getNode(node->id()))
	{
		return;
	}
	
	if (!_parser.tree()->getNode(_parents.value(node->id())))
	{
		insertIntoTree(_nodes.value(_parents.value(node->id())));
	}
	
	_parser.tree()->getNode(_parents.value(node->id()))->addChild(node);
}

void SDStrategy::addMetrics()
{
	_parser.tree()->addAttributeMap("id", AttributeMap::Numeric);
	_parser.tree()->addAttributeMap("depth", AttributeMap::Numeric);
	
	for (Node* node : _nodes)
	{
		node->setAttribute("id", node->id());
		node->setAttribute("depth", node->depth());
	}
	
	for (const QVariantMap& metricMeta : executeQuery("SELECT id, name, type FROM metricsmeta WHERE 1 ORDER BY id"))
	{
		_parser.tree()->addAttributeMap(
			metricMeta["name"].toString().toStdString(),
			metricMeta["type"].toInt() == 1 ? AttributeMap::Numeric : AttributeMap::Nominal
		);
		
		_metrics[metricMeta["id"].toInt()] = metricMeta["name"].toString();
	}
	
	for (const QVariantMap& metricSet : executeQuery("SELECT timestamp FROM metricssets WHERE 1 ORDER BY timestamp LIMIT 1"))
	{
		for (const QVariantMap& metricData : executeQuery("SELECT itemId, metricId, value FROM metricsdata WHERE timestamp = " + metricSet["timestamp"].toString() + " ORDER BY itemId"))
		{
			_nodes[metricData["itemId"].toInt()]->setAttribute(
				_metrics[metricData["metricId"].toInt()].toStdString(),
				metricData["value"].toString().toStdString()
			);
		}
		
		return;
	}
}

QList<QVariantMap> SDStrategy::executeQuery(const QString& statement) const
{
	QSqlQuery query(statement, _parser.database());
	
	if (query.exec())
	{
		QList<QVariantMap> rows;
		QSqlRecord record = query.record();
		QHash<QString, int> indices;
		
		for (unsigned i = 0; i < record.count(); ++i)
		{
			indices[record.fieldName(i)] = i;
		}
		
		while (query.next())
		{
			QVariantMap row;
			
			for (const QString& fieldName : indices.keys())
			{
				row[fieldName] = query.value(indices[fieldName]);
			}
			
			rows << row;
		}
		
		return rows;
	}
	else
	{
		qDebug() << query.executedQuery();
		qDebug() << "Error:" << query.lastError();
		
		return QList<QVariantMap>();
	}
}
