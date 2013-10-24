
#include <algorithm>
#include <queue>
#include <iostream>
#include <sstream>

#include <treezeug/Tree.h>


namespace zeug
{

Tree::Tree(const std::string & name)
:   m_name(name)
,   m_root(new Node())
,   m_nextId(0)
,   m_depth(0)
{
    registerNode(m_root, true);
}

Tree::~Tree()
{
	delete m_root;

	for (const std::pair<std::string, AttributeMap*> & pair : m_attributeMaps)
	{
		delete pair.second;
	}
}

Tree * Tree::copy() const
{
	Tree * newTree = new Tree(m_name);

	nodesDo([=](const Node * node) 
    {
		Node * newNode = new Node(node->id());
		newNode->setName(node->name());

		if (newNode->id() == 0)
			newTree->setRoot(newNode);
		else
			newTree->getNode(node->parent()->id())->addChild(newNode);
	});

	for (const std::string & attribute : m_attributes)
	{
		newTree->addAttributeMap(attribute, attributeMapType(attribute));

		nodesDo([=](const Node * node) 
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

Tree * Tree::restrictTo(Node * newRoot) const
{
	Tree* newTree = new Tree(m_name);
	
	newTree->deregisterNode(newTree->root());
	
	newRoot->withAllChildrenDo([=](const Node * node) 
    {
		Node * newNode = new Node(node->id());
		newNode->setName(node->name());

		if (newNode->id() == newRoot->id())
			newTree->setRoot(newNode, newRoot->id());
		else
			newTree->getNode(node->parent()->id())->addChild(newNode);
	});

	for (const std::string & attribute : m_attributes)
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
    return m_name;
}

void Tree::setName(const std::string & name)
{
    m_name = name;
}

Node * Tree::root()
{
	return m_root;
}

const Node * Tree::root() const
{
	return m_root;
}

void Tree::setRoot(Node * node, int id)
{
	node->m_id = id;
	registerNode(node, true);
	node->m_parent = nullptr;
	m_root = node;
}

unsigned Tree::size() const
{
	return m_idMap.size();
}

int Tree::maxId() const
{
	return m_nextId - 1;
}

unsigned Tree::depth() const
{
	return m_depth;
}

Node * Tree::getNode(int id) const
{
	if (!m_idMap.count(id))
		return nullptr;

	return m_idMap.at(id);
}

Node * Tree::getNodeByPath(const std::string & path, char separator)
{
	if (path.empty()) 
        return nullptr;

    if (path == std::to_string(separator)) 
        return m_root;

    std::stringstream ss(path);
	std::string item;

    Node * node = m_root;

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
	return m_attributes;
}

bool Tree::hasAttributeMap(const std::string & name) const
{
	return m_attributeMaps.count(name) > 0;
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

	m_attributeMaps[name] = new AttributeMap(name, type);
	m_attributes.push_back(name);
}

AttributeMap::Type Tree::attributeMapType(const std::string & name) const
{
	if (!hasAttributeMap(name))
		return AttributeMap::None;

	return m_attributeMaps.at(name)->type();
}

void Tree::renormalizeAttributeForLeaves(const std::string& attribute)
{
    if (!hasAttributeMap(attribute))
        return;

    m_attributeMaps.at(attribute)->renormalizeForLeaves();
}

void Tree::setAttribute(const Node * node, const std::string & name, double value)
{
	if (!hasAttributeMap(name))
		return;

	m_attributeMaps[name]->addAttribute(node, value);
}

void Tree::setAttribute(const Node * node, const std::string & name, const std::string & value)
{
	if (!m_attributeMaps.count(name))
		return;

	AttributeMap * map = m_attributeMaps[name];
	if (map)
		map->addAttribute(node, value);
}

const Attribute * Tree::attribute(const Node * node, const std::string & name) const
{
	if (!m_attributeMaps.count(name))
		return nullptr;

	return m_attributeMaps.at(name)->attributeFor(node);
}

void Tree::registerNode(Node * node, bool silent)
{
	node->m_tree = this;

	if (node->m_id >= 0)
	{
		m_nextId = std::max(node->m_id + 1, m_nextId+1);
	}
	else
	{
		node->m_id = m_nextId;

		m_nextId++;
	}

	if (m_idMap.count(node->m_id))
	{
		if (!silent)
		{
			std::cout << "Replace node " << node->m_id << std::endl;
		}

		m_idMap[node->m_id]->reparentChildrenTo(node);

		delete m_idMap[node->m_id];
	}

	m_depth = std::max(m_depth, node->depth());

	m_idMap[node->m_id] = node;
}

void Tree::deregisterNode(Node * node)
{
	if (m_root == node)
		m_root = nullptr;
	
	node->m_tree = nullptr;

	m_idMap.erase(node->m_id);
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

	queue.push(m_root);

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

	queue.push(m_root);

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
