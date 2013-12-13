
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
, m_root(m_data->m_root)
{
}

Tree::Tree(std::shared_ptr<TreeData> data)
: m_data(data)
, m_root(m_data->m_root)
{
}

Tree::Tree(const Tree& other)
: m_data(other.m_data)
, m_root(other.m_root)
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
    Tree* newTree = copy();
    newTree->m_root = newRoot;
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
    if (m_root == nullptr)
    {
        m_root = m_data->m_root;
    }

    return m_root;
}

const Node * Tree::root() const
{
    if (m_root == nullptr)
    {
        m_root = m_data->m_root;
    }

    return m_root;
}

void Tree::setRoot(Node * node, int id)
{
    if (m_root == m_data->m_root)
    {
        std::cout << "#warning: replacing inner root while Trees have pointers to old root";
        m_root = nullptr;
    }

    m_data->setRoot(node, id);
}

unsigned Tree::size() const
{
    return m_root->size();
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
    m_root->withAllChildrenDo(action);
}

void Tree::nodesDo(std::function<void(const Node*)> action) const
{
    const_cast<const Node*>(m_root)->withAllChildrenDo(action); // const cast to prevent unnecessary ambiguous warning (gcc compiler bug?)
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

void Tree::nodesOrderedByDepthDo(std::function<void(const Node*)> action) const
{
	std::queue<const Node*> queue;

    queue.push(root());

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
