
#include <algorithm>
#include <queue>
#include <iostream>
#include <sstream>

#include <treezeug/Tree.h>

#include "TreeData.h"

namespace zeug
{

Tree::Tree(const std::string & name)
: m_data(new TreeData(name))
{
}

Tree::Tree(std::shared_ptr<TreeData> data)
: m_data(data)
{
}

Tree::Tree(const Tree& other)
: m_data(other.m_data)
{
}

Tree::~Tree()
{
}

Tree * Tree::copy() const
{
    return new Tree(*this);
}

Tree * Tree::restrictTo(Node * newRoot) const
{
    Tree* newTree = new Tree(m_data->m_name);
	
    newTree->m_data->deregisterNode(newTree->root());
	
	newRoot->withAllChildrenDo([=](const Node * node) 
    {
		Node * newNode = new Node(node->id());
		newNode->setName(node->name());

		if (newNode->id() == newRoot->id())
			newTree->setRoot(newNode, newRoot->id());
		else
			newTree->getNode(node->parent()->id())->addChild(newNode);
	});

    for (const std::string & attribute : m_data->m_attributes)
	{
		newTree->addAttributeMap(attribute, attributeMapType(attribute));

		newRoot->withAllChildrenDo([=](const Node * node) 
        {
			if (node->hasAttribute(attribute))
			{
				const Attribute * attr = node->attribute(attribute);

				if (attr->isNumeric())
					newTree->getNode(node->id())->setAttribute(attribute, attr->numericValue());
				else
					newTree->getNode(node->id())->setAttribute(attribute, attr->asNominal()->valueName());
			}
		});
	}
	return newTree;
}

Tree * Tree::restrictTo(int id) const
{
	Node* newRoot = getNode(id);
	
	if (!newRoot)
		return nullptr;
	
	return restrictTo(newRoot);
}

const std::string & Tree::name() const
{
    return m_data->m_name;
}

void Tree::setName(const std::string & name)
{
    m_data->m_name = name;
}

Node * Tree::root()
{
    return m_data->m_root;
}

const Node * Tree::root() const
{
    return m_data->m_root;
}

void Tree::setRoot(Node * node, int id)
{
    m_data->setRoot(node, id);
}

unsigned Tree::size() const
{
    return m_data->m_idMap.size();
}

int Tree::maxId() const
{
    return m_data->m_nextId - 1;
}

unsigned Tree::depth() const
{
    return m_data->m_depth;
}

Node * Tree::getNode(int id) const
{
    if (!m_data->m_idMap.count(id))
		return nullptr;

    return m_data->m_idMap.at(id);
}

Node * Tree::getNodeByPath(const std::string & path, char separator)
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

const std::vector<std::string> & Tree::attributes() const
{
    return m_data->m_attributes;
}

bool Tree::hasAttributeMap(const std::string & name) const
{
    return m_data->hasAttributeMap(name);
}

void Tree::addAttributeMap(const std::string & name, AttributeMap::Type type)
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

AttributeMap::Type Tree::attributeMapType(const std::string & name) const
{
	if (!hasAttributeMap(name))
		return AttributeMap::None;

    return m_data->m_attributeMaps.at(name)->type();
}

void Tree::renormalizeAttributeForLeaves(const std::string& attribute)
{
    if (!hasAttributeMap(attribute))
        return;

    m_data->m_attributeMaps.at(attribute)->renormalizeForLeaves();
}

void Tree::nodesDo(std::function<void(Node*)> action)
{
    m_data->m_root->withAllChildrenDo(action);
}

void Tree::nodesDo(std::function<void(const Node*)> action) const
{
    const_cast<const Node*>(m_data->m_root)->withAllChildrenDo(action); // const cast to prevent unnecessary ambiguous warning (gcc compiler bug?)
}

void Tree::leavesDo(std::function<void(Node*)> action)
{
	nodesDo([&action](Node * node) 
    {
		if (node->isLeaf()) 
            action(node);
	});
}

void Tree::leavesDo(std::function<void(const Node*)> action) const
{
	nodesDo([&action](const Node * node) 
    {
		if (node->isLeaf()) 
            action(node);
	});
}

void Tree::nodesOrderedByDepthDo(std::function<void(Node*)> action)
{
	std::queue<Node*> queue;

    queue.push(m_data->m_root);

	while (!queue.empty())
	{
		Node * current = queue.front();
		queue.pop();

		action(current);

		for (Node * child : current->children())
			queue.push(child);
	}
}

void Tree::nodesOrderedByDepthDo(std::function<void(const Node*)> action) const
{
	std::queue<const Node*> queue;

    queue.push(m_data->m_root);

	while (!queue.empty())
	{
		const Node* current = queue.front();
		queue.pop();

		action(current);

		for (const Node * child : current->children())
			queue.push(child);
	}
}

} // namespace zeug
