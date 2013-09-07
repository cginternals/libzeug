#pragma once

#include <treezeug/Attribute.h>

#include <functional>
#include <string>
#include <vector>

class Tree;

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

	std::string path(char separator = '/') const;
	Node* getChildByName(const std::string& name);

	int id() const;

	void setAttribute(const std::string& name, double value);
	void setAttribute(const std::string& name, const std::string& value);
	const Attribute* attribute(const std::string& name) const;
	bool hasAttribute(const std::string& name) const;

	const std::vector<Node*>& children() const;
    std::vector<Node*>& children();
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
