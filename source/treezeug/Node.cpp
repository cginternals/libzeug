
#include <algorithm>

#include <treezeug/Node.h>
#include <treezeug/Tree.h>

namespace zeug
{

Node::Node()
:   m_tree(nullptr)
,   m_id(-1)
,   m_parent(nullptr)
{
}

Node::Node(int id)
:   m_tree(nullptr)
,   m_id(id)
,   m_parent(nullptr)
{
}

Node::~Node()
{
	for (Node * child : m_children)
	{
		delete child;
	}
}

bool Node::isLeaf() const
{
	return m_children.empty();
}

bool Node::isRoot() const
{
	return !m_parent;
}

int Node::id() const
{
	return m_id;
}

const std::string & Node::name() const
{
	return m_name;
}

void Node::setName(const std::string& name)
{
	m_name = name;
}

std::string Node::path(char separator) const
{
	std::string path;
	const Node* current = this;
	while (!current->isRoot())
	{
		path = path.empty() ? current->name() : current->name() + separator + path;
		current = current->parent();
	}

	return separator + path;
}

Node * Node::getChildByName(const std::string & name)
{
	for (Node * node: m_children)
	{
		if (node->name() == name)
			return node;
	}

	return nullptr;
}

void Node::setAttribute(const std::string & name, double value)
{
	m_tree->setAttribute(this, name, value);
}

void Node::setAttribute(const std::string & name, const std::string & value)
{
	m_tree->setAttribute(this, name, value);
}

const Attribute * Node::attribute(const std::string & name) const
{
	return m_tree->attribute(this, name);
}

bool Node::hasAttribute(const std::string & name) const
{
	return attribute(name) != nullptr;
}

const std::vector<Node*> & Node::children() const
{
	return m_children;
}

std::vector<Node*> & Node::children()
{
    return m_children;
}

void Node::childrenDo(std::function<void(Node*)> action)
{
	for (Node * child: m_children)
		action(child);
}

void Node::childrenDo(std::function<void(const Node*)> action) const
{
	for (const Node * child: m_children)
		action(child);
}

void Node::withAllChildrenDo(std::function<void(Node*)> action)
{
	action(this);

	for (Node * child: m_children)
		child->withAllChildrenDo(action);
}

void Node::withAllChildrenDo(std::function<void(const Node*)> action) const
{
	action(this);

	for (const Node * child: m_children)
		child->withAllChildrenDo(action);
}

void Node::addChild(Node * child)
{
	m_children.push_back(child);
	child->m_parent = this;
	m_tree->registerNode(child);
}

void Node::reparentChildrenTo(Node * newParent)
{
	for (Node * child : m_children)
	{
		newParent->m_children.push_back(child);
		child->m_parent = newParent;
	}

	m_children.clear();
}

unsigned Node::depth() const
{
	if (!m_parent) 
        return 0;

    return m_parent->depth() + 1;
}

const Node * Node::parent() const
{
	return m_parent;
}

std::vector<Node*> Node::siblings() const
{
	std::vector<Node*> nodes;

	if (m_parent)
	{
		for (Node * sibling: m_parent->children())
		{
			if (sibling != this) 
                nodes.push_back(sibling);
		}
	}
	return nodes;
}

const Node * Node::previousSibling() const
{
	if (!m_parent) return nullptr;

	std::vector<Node*>::iterator current = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);

	if (current == m_parent->m_children.begin() || current == m_parent->m_children.end())
		return nullptr;

	return *(current - 1);
}

const Node * Node::nextSibling() const
{
	if (!m_parent) return nullptr;

	auto current = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);

	if (current == m_parent->m_children.end() || current + 1 == m_parent->m_children.end())
		return nullptr;

	return *(current + 1);
}

const Node * Node::firstChild() const
{
	if (m_children.empty()) 
        return nullptr;

	return m_children.front();
}

bool Node::hasChildren() const
{
	return m_children.size() > 0;
}

const Tree * Node::tree() const
{
	return m_tree;
}

} // namespace zeug
