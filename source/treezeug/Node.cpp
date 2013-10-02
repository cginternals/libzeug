#include <treezeug/Node.h>

#include <treezeug/Tree.h>

#include <algorithm>

Node::Node()
: _tree(nullptr)
, _id(-1)
, _parent(nullptr)
{
}

Node::Node(int id)
: _tree(nullptr)
, _id(id)
, _parent(nullptr)
{
}

Node::~Node()
{
	for (Node* child : _children)
	{
		delete child;
	}
}

bool Node::isLeaf() const
{
	return _children.empty();
}

bool Node::isRoot() const
{
	return !_parent;
}

int Node::id() const
{
	return _id;
}

const std::string& Node::name() const
{
	return _name;
}

void Node::setName(const std::string& name)
{
	_name = name;
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

Node* Node::getChildByName(const std::string& name)
{
	for (Node* node: _children)
	{
		if (node->name() == name)
			return node;
	}

	return nullptr;
}

void Node::setAttribute(const std::string& name, double value)
{
	_tree->setAttribute(this, name, value);
}

void Node::setAttribute(const std::string& name, const std::string& value)
{
	_tree->setAttribute(this, name, value);
}

const Attribute* Node::attribute(const std::string& name) const
{
	return _tree->attribute(this, name);
}

bool Node::hasAttribute(const std::string& name) const
{
	return attribute(name) != nullptr;
}

const std::vector<Node*>& Node::children() const
{
	return _children;
}

std::vector<Node*>& Node::children()
{
    return _children;
}

void Node::childrenDo(std::function<void(Node*)> action)
{
	for (Node* child: _children)
	{
		action(child);
	}
}

void Node::childrenDo(std::function<void(const Node*)> action) const
{
	for (const Node* child: _children)
	{
		action(child);
	}
}

void Node::withAllChildrenDo(std::function<void(Node*)> action)
{
	action(this);

	for (Node* child: _children)
	{
		child->withAllChildrenDo(action);
	}
}

void Node::withAllChildrenDo(std::function<void(const Node*)> action) const
{
	action(this);

	for (const Node* child: _children)
	{
		child->withAllChildrenDo(action);
	}
}

void Node::addChild(Node* child)
{
	_children.push_back(child);
	child->_parent = this;
	_tree->registerNode(child);
}

void Node::reparentChildrenTo(Node* newParent)
{
	for (Node* child : _children)
	{
		newParent->_children.push_back(child);
		child->_parent = newParent;
	}

	_children.clear();
}

unsigned Node::depth() const
{
	if (!_parent) return 0;
	return _parent->depth() + 1;
}

const Node* Node::parent() const
{
	return _parent;
}

std::vector<Node*> Node::siblings() const
{
	std::vector<Node*> nodes;

	if (_parent)
	{
		for (Node* sibling: _parent->children())
		{
			if (sibling != this) nodes.push_back(sibling);
		}
	}

	return nodes;
}

const Node* Node::previousSibling() const
{
	if (!_parent) return nullptr;

	std::vector<Node*>::iterator current = std::find(_parent->_children.begin(), _parent->_children.end(), this);

	if (current == _parent->_children.begin() || current == _parent->_children.end())
	{
		return nullptr;
	}

	return *(current-1);
}

const Node* Node::nextSibling() const
{
	if (!_parent) return nullptr;

	std::vector<Node*>::iterator current = std::find(_parent->_children.begin(), _parent->_children.end(), this);

	if (current == _parent->_children.end() || current+1 == _parent->_children.end())
	{
		return nullptr;
	}

	return *(current+1);
}

const Node* Node::firstChild() const
{
	if (_children.empty()) return nullptr;

	return _children.front();
}

bool Node::hasChildren() const
{
	return _children.size() > 0;
}

const Tree* Node::tree() const
{
	return _tree;
}
