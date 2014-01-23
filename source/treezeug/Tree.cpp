
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
    Node* newRoot = const_cast<Node*>(getNode(id));
	
	if (!newRoot)
		return nullptr;
	
	return restrictTo(newRoot);
}

const std::string & Tree::name() const
{
    return m_data->m_name;
}

const Node * Tree::root() const
{
    return m_root;
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

const Node * Tree::getNode(int id) const
{
    if (!m_data->m_idMap.count(id))
		return nullptr;

    return m_data->m_idMap.at(id);
}

const Node * Tree::getNodeByPath(const std::string & path, char separator) const
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

AttributeMap::Type Tree::attributeMapType(const std::string & name) const
{
	if (!hasAttributeMap(name))
		return AttributeMap::None;

    return m_data->m_attributeMaps.at(name)->type();
}

void Tree::nodesDo(std::function<void(const Node*)> action) const
{
    const_cast<const Node*>(m_root)->withAllChildrenDo(action); // const cast to prevent unnecessary ambiguous warning (gcc compiler bug?)
}

void Tree::leavesDo(std::function<void(const Node*)> action) const
{
	nodesDo([&action](const Node * node) 
    {
		if (node->isLeaf()) 
            action(node);
	});
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
