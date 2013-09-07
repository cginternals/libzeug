#include <Tree.h>

#include <algorithm>
#include <queue>
#include <iostream>
#include <sstream>

Tree::Tree(const std::string& name)
: _name(name)
, _root(new Node())
, _nextId(0)
, _depth(0)
{
    registerNode(_root, true);
}

Tree::~Tree()
{
	delete _root;

	for (const std::pair<std::string, AttributeMap*>& pair : _attributeMaps)
	{
		delete pair.second;
	}
}

Tree* Tree::copy() const
{
	Tree* newTree = new Tree(_name);

	nodesDo([=](const Node* node) {
		Node* newNode = new Node(node->id());
		newNode->setName(node->name());

		if (newNode->id() == 0)
		{
			newTree->setRoot(newNode);
		}
		else
		{
			newTree->getNode(node->parent()->id())->addChild(newNode);
		}
	});

	for (const std::string& attribute : _attributes)
	{
		newTree->addAttributeMap(attribute, attributeMapType(attribute));

		nodesDo([=](const Node* node) {
			if (node->hasAttribute(attribute))
			{
				const Attribute* attr = node->attribute(attribute);

				if (attr->isNumeric())
				{
					newTree->getNode(node->id())->setAttribute(attribute, attr->numericValue());
				}
				else
				{
					newTree->getNode(node->id())->setAttribute(attribute, attr->asNominal()->valueName());
				}
			}
		});
	}

	return newTree;
}

Tree* Tree::restrictTo(Node* newRoot) const
{
	Tree* newTree = new Tree(_name);
	
	newTree->deregisterNode(newTree->root());
	
	newRoot->withAllChildrenDo([=](const Node* node) {
		Node* newNode = new Node(node->id());
		newNode->setName(node->name());

		if (newNode->id() == newRoot->id())
		{
			newTree->setRoot(newNode, newRoot->id());
		}
		else
		{
			newTree->getNode(node->parent()->id())->addChild(newNode);
		}
	});

	for (const std::string& attribute : _attributes)
	{
		newTree->addAttributeMap(attribute, attributeMapType(attribute));

		newRoot->withAllChildrenDo([=](const Node* node) {
			if (node->hasAttribute(attribute))
			{
				const Attribute* attr = node->attribute(attribute);

				if (attr->isNumeric())
				{
					newTree->getNode(node->id())->setAttribute(attribute, attr->numericValue());
				}
				else
				{
					newTree->getNode(node->id())->setAttribute(attribute, attr->asNominal()->valueName());
				}
			}
		});
	}

	return newTree;
}

Tree* Tree::restrictTo(int id) const
{
	Node* newRoot = getNode(id);
	
	if (!newRoot)
	{
		return nullptr;
	}
	
	return restrictTo(newRoot);
}

const std::string& Tree::name() const
{
    return _name;
}

void Tree::setName(const std::string& name)
{
    _name = name;
}

Node* Tree::root()
{
	return _root;
}

const Node* Tree::root() const
{
	return _root;
}

void Tree::setRoot(Node* node, int id)
{
	node->_id = id;
	registerNode(node, true);
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

Node* Tree::getNodeByPath(const std::string& path, char separator)
{
	if (path.empty()) return nullptr;
	if (path == std::to_string(separator)) return _root;

    std::stringstream ss(path);
	std::string item;
    Node* node = _root;

	std::getline(ss, item, separator);
	if (!item.empty()) return nullptr;

    while (node && std::getline(ss, item, separator))
	{
        node = node->getChildByName(item);
    }

    return node;
}

const std::vector<std::string>& Tree::attributes() const
{
	return _attributes;
}

bool Tree::hasAttributeMap(const std::string& name) const
{
	return _attributeMaps.count(name) > 0;
}

void Tree::addAttributeMap(const std::string& name, AttributeMap::Type type)
{
	if (hasAttributeMap(name))
	{
		if (attributeMapType(name) != type)
		{
			std::cout << "Try to overwrite AttributeMap " << name << " with differing type";
		}

		return;
	}

	_attributeMaps[name] = new AttributeMap(name, type);
	_attributes.push_back(name);
}

AttributeMap::Type Tree::attributeMapType(const std::string& name) const
{
	if (!hasAttributeMap(name))
	{
		return AttributeMap::None;
	}

	return _attributeMaps.at(name)->type();
}

void Tree::setAttribute(const Node* node, const std::string& name, double value)
{
	if (!hasAttributeMap(name))
	{
		return;
	}

	_attributeMaps[name]->addAttribute(node, value);
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

void Tree::registerNode(Node* node, bool silent)
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
		if (!silent)
		{
			std::cout << "Replace node " << node->_id << std::endl;
		}

		_idMap[node->_id]->reparentChildrenTo(node);

		delete _idMap[node->_id];
	}

	_depth = std::max(_depth, node->depth());

	_idMap[node->_id] = node;
}

void Tree::deregisterNode(Node* node)
{
	if (_root == node)
	{
		_root = nullptr;
	}
	
	node->_tree = nullptr;

	_idMap.erase(node->_id);
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
