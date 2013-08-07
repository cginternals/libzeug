#include <Tree.h>

#include <algorithm>
#include <queue>
#include <iostream>

Tree::Tree()
: _root(new Node())
, _nextId(0)
, _depth(0)
{
	registerNode(_root);
}

Tree::~Tree()
{
	delete _root;

	for (const std::pair<std::string, AttributeMap*>& pair : _attributeMaps)
	{
		delete pair.second;
	}
}

Node* Tree::root()
{
	return _root;
}

const Node* Tree::root() const
{
	return _root;
}

void Tree::setRoot(Node* node)
{
	node->_id = 0;
	registerNode(node);
	node->_parent = nullptr;
	_root = node;
}

unsigned Tree::size() const
{
	return _idMap.size();
}

int Tree::maxId() const
{
	return _nextId - 1;
}

unsigned Tree::depth() const
{
	return _depth;
}

Node* Tree::getNode(int id) const
{
	if (!_idMap.count(id))
	{
		return nullptr;
	}

	return _idMap.at(id);
}

const std::vector<std::string>& Tree::attributes() const
{
	return _attributes;
}

void Tree::addAttributeMap(const std::string&name, AttributeMap::Type type)
{
	_attributeMaps[name] = new AttributeMap(name, type);
	_attributes.push_back(name);
}

void Tree::setAttribute(const Node* node, const std::string& name, double value)
{
	if (!_attributeMaps.count(name))
	{
		return;
	}

	AttributeMap* map = _attributeMaps[name];
	if (map)
	{
		map->addAttribute(node, value);
	}
}

void Tree::setAttribute(const Node* node, const std::string& name, const std::string& value)
{
	if (!_attributeMaps.count(name))
	{
		return;
	}

	AttributeMap* map = _attributeMaps[name];
	if (map)
	{
		map->addAttribute(node, value);
	}
}

const Attribute* Tree::attribute(const Node* node, const std::string& name) const
{
	if (!_attributeMaps.count(name))
	{
		return nullptr;
	}

	return _attributeMaps.at(name)->attributeFor(node);
}

void Tree::registerNode(Node* node)
{
	node->_tree = this;

	if (node->_id >= 0)
	{
		_nextId = std::max(node->_id + 1, _nextId+1);
	}
	else
	{
		node->_id = _nextId;

		_nextId++;
	}

	if (_idMap.count(node->_id))
	{
		std::cout << "Replace node " << node->_id;
		_idMap[node->_id]->reparentChildrenTo(node);

		delete _idMap[node->_id];
	}

	_depth = std::max(_depth, node->depth());

	_idMap[node->_id] = node;
}

void Tree::nodesDo(std::function<void(Node*)> action)
{
	_root->withAllChildrenDo(action);
}

void Tree::nodesDo(std::function<void(const Node*)> action) const
{
	const_cast<const Node*>(_root)->withAllChildrenDo(action); // const cast to prevent unnecessary ambiguous warning (gcc compiler bug?)
}

void Tree::leavesDo(std::function<void(Node*)> action)
{
	nodesDo([&action](Node* node) {
		if (node->isLeaf()) action(node);
	});
}

void Tree::leavesDo(std::function<void(const Node*)> action) const
{
	nodesDo([&action](const Node* node) {
		if (node->isLeaf()) action(node);
	});
}

void Tree::nodesOrderedByDepthDo(std::function<void(Node*)> action)
{
	std::queue<Node*> queue;

	queue.push(_root);

	while (!queue.empty())
	{
		Node* current = queue.front();
		queue.pop();

		action(current);

		for (Node* child : current->children())
		{
			queue.push(child);
		}
	}
}

void Tree::nodesOrderedByDepthDo(std::function<void(const Node*)> action) const
{
	std::queue<const Node*> queue;

	queue.push(_root);

	while (!queue.empty())
	{
		const Node* current = queue.front();
		queue.pop();

		action(current);

		for (const Node* child : current->children())
		{
			queue.push(child);
		}
	}
}


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

const std::vector<Node*>& Node::children() const
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
