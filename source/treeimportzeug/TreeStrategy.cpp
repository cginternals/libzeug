#include <treeimportzeug/TreeStrategy.h>

#include "MutableTree.h"

namespace zeug
{

TreeStrategy::TreeStrategy()
{
}

QSet<QString> TreeStrategy::wantedFileSuffixes() const
{
    return QSet<QString>() << "xml";
}

bool TreeStrategy::wantsToProcess(const QString& tagName, const QXmlAttributes & attributes) const
{
	return tagName == "tree";
}

void TreeStrategy::clear()
{
	m_stack.clear();
}

void TreeStrategy::start()
{
	m_tree->addAttributeMap("size", AttributeMap::Numeric);
}

void TreeStrategy::finish()
{
	Node * root = m_tree->root();

	float totalSize = 0;
	root->childrenDo([&totalSize](Node * node) {
        totalSize += node->attribute("size")->numericValue(); });

	root->setName("<root>");
	root->setAttribute("size", totalSize);

    m_tree->renormalizeAttributesForLeaves();
}

bool TreeStrategy::startElement(const QString & name, const QXmlAttributes & attributes)
{
	if (name != "directory" && name != "file")
		return true;

	if (m_stack.size() == 0)
	{
		m_stack.push(m_tree->root());
		return true;
	}

	Node * node = new Node();
	m_stack.top()->addChild(node);

	node->setName(attributes.value("name").toStdString());
	node->setAttribute("size", attributes.value("size").toFloat());

	m_stack.push(node);

	return true;
}

bool TreeStrategy::endElement(const QString & name)
{
	if (name != "directory" && name != "file")
		return true;

	m_stack.pop();
	return true;
}

bool TreeStrategy::handleCharacters(const QString & characters)
{
	return true;
}

} // namespace zeug
