#pragma once

#include <AttributeMap.h>

#include <functional>

#include <string>
#include <unordered_map>
#include <vector>

class Node;

class Tree
{
	friend class Node;
public:
	Tree();
	virtual ~Tree();

	Node* root();
	const Node* root() const;
	void setRoot(Node* node);

	unsigned size() const;
	int maxId() const;

	Node* getNode(int id) const;

	void nodesDo(std::function<void(Node*)> action);
	void nodesDo(std::function<void(const Node*)> action) const;
	void nodesOrderedByDepthDo(std::function<void(Node*)> action);
	void nodesOrderedByDepthDo(std::function<void(const Node*)> action) const;
	void leavesDo(std::function<void(Node*)> action);
	void leavesDo(std::function<void(const Node*)> action) const;

	bool hasAttributeMap(const std::string& name) const;
	void addAttributeMap(const std::string& name, AttributeMap::Type type);
	AttributeMap::Type attributeMapType(const std::string& name) const;
	const std::vector<std::string>& attributes() const;

	unsigned depth() const;

	Tree* copy() const;
protected:
	Node* _root;
	std::unordered_map<int, Node*> _idMap;
	int _nextId;
	unsigned _depth;
	std::unordered_map<std::string, AttributeMap*> _attributeMaps;
	std::vector<std::string> _attributes;

	void registerNode(Node* node, bool silent = false);

	void setAttribute(const Node* node, const std::string& name, double value);
	void setAttribute(const Node* node, const std::string& name, const std::string& value);
	const Attribute* attribute(const Node* node, const std::string& name) const;
};

class Node
{
	friend class Tree;
public:
	Node();
	Node(int id);
	virtual ~Node();

	bool isLeaf() const;
	bool isRoot() const;

	const std::string& name() const;
	void setName(const std::string& name);

	int id() const;

	void setAttribute(const std::string& name, double value);
	void setAttribute(const std::string& name, const std::string& value);
	const Attribute* attribute(const std::string& name) const;
	bool hasAttribute(const std::string& name) const;

	const std::vector<Node*>& children() const;
	void addChild(Node* child);
	void addChildren(const std::vector<Node*>& children);

	void childrenDo(std::function<void(Node*)> action);
	void childrenDo(std::function<void(const Node*)> action) const;
	void withAllChildrenDo(std::function<void(Node*)> action);
	void withAllChildrenDo(std::function<void(const Node*)> action) const;

	unsigned depth() const;
	bool hasChildren() const;

	const Node* parent() const;
	const Node* previousSibling() const;
	const Node* nextSibling() const;
	const Node* firstChild() const;
	std::vector<Node*> siblings() const;

	const Tree* tree() const;
protected:
	Tree* _tree;
	int _id;
	Node* _parent;
	std::vector<Node*> _children;
	std::string _name;

	void reparentChildrenTo(Node* newParent);
};
