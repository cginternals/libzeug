
#include <algorithm>
#include <queue>
#include <iostream>
#include <sstream>

#include "MutableTree.h"

#include "../treezeug/TreeData.h"

namespace zeug
{

MutableTree::MutableTree(const std::string & name)
: Tree(name)
{
}

MutableTree::MutableTree(std::shared_ptr<TreeData> data)
: Tree(data)
{
}

MutableTree::MutableTree(const Tree& other)
: Tree(other)
{
}

MutableTree::~MutableTree()
{
}

void MutableTree::setName(const std::string & name)
{
    m_data->m_name = name;
}

Node* MutableTree::root()
{
    return m_root;
}

Node * MutableTree::getNode(int id)
{
    if (!m_data->m_idMap.count(id))
        return nullptr;

    return m_data->m_idMap.at(id);
}

Node * MutableTree::getNodeByPath(const std::string & path, char separator)
{
    if (path.empty())
        return nullptr;

    if (path == std::to_string(separator))
        return m_data->m_root;

    std::stringstream ss(path);
    std::string item;

    Node * node = m_data->m_root;

    std::getline(ss, item, separator);
    if (!item.empty())
        return nullptr;

    while (node && std::getline(ss, item, separator))
    {
        node = node->getChildByName(item);
    }

    return node;
}

void MutableTree::setRoot(Node * node, int id)
{
    m_data->setRoot(node, id);

    m_root = m_data->m_root;
}

void MutableTree::addAttributeMap(const std::string & name, AttributeMap::Type type)
{
	if (hasAttributeMap(name))
	{
		if (attributeMapType(name) != type)
		{
			std::cout << "Try to overwrite AttributeMap " << name << " with differing type";
		}
		return;
	}

    m_data->m_attributeMaps[name] = new AttributeMap(name, type);
    m_data->m_attributes.push_back(name);
}

void MutableTree::renormalizeAttributesForLeaves()
{
    for (const std::string& attribute : m_data->m_attributes)
    {
        renormalizeAttributeForLeaves(attribute);
    }
}

void MutableTree::renormalizeAttributeForLeaves(const std::string& attribute)
{
    if (!hasAttributeMap(attribute))
        return;

    m_data->m_attributeMaps.at(attribute)->renormalizeForLeaves();
}

void MutableTree::nodesDo(std::function<void(Node*)> action)
{
    m_root->withAllChildrenDo(action);
}

void MutableTree::leavesDo(std::function<void(Node*)> action)
{
	nodesDo([&action](Node * node) 
    {
		if (node->isLeaf()) 
            action(node);
	});
}

void MutableTree::nodesOrderedByDepthDo(std::function<void(Node*)> action)
{
	std::queue<Node*> queue;

    queue.push(root());

	while (!queue.empty())
	{
		Node * current = queue.front();
		queue.pop();

		action(current);

		for (Node * child : current->children())
			queue.push(child);
	}
}

} // namespace zeug
