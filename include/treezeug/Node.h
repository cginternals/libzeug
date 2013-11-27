#pragma once

#include <functional>
#include <string>
#include <vector>

#include <treezeug/treezeug.h>
#include <treezeug/Attribute.h>


namespace zeug
{

class TreeData;

class TREEZEUG_API Node
{
    friend class TreeData;

public:
	Node();
	Node(int id);
	virtual ~Node();

	bool isLeaf() const;
	bool isRoot() const;

	const std::string & name() const;
	void setName(const std::string & name);

	std::string path(char separator = '/') const;
	Node * getChildByName(const std::string & name);

	int id() const;
    int size() const;

	void setAttribute(const std::string & name, double value);
	void setAttribute(const std::string & name, const std::string & value);

	const Attribute * attribute(const std::string & name) const;
	bool hasAttribute(const std::string & name) const;

	const std::vector<Node*> & children() const;
    std::vector<Node*> & children();

    void addChild(Node * child);
    void addChildren(const std::vector<Node*> & children);

	void childrenDo(std::function<void(Node*)> action);
	void childrenDo(std::function<void(const Node*)> action) const;
	void withAllChildrenDo(std::function<void(Node*)> action);
	void withAllChildrenDo(std::function<void(const Node*)> action) const;

	unsigned depth() const;
	bool hasChildren() const;

	const Node * parent() const;
	const Node * previousSibling() const;
	const Node * nextSibling() const;
	const Node * firstChild() const;
    std::vector<Node*> siblings() const;

protected:
    void reparentChildrenTo(Node* newParent);
    void manipulateCachedSize(int delta);

protected:
    TreeData* m_data;
    int m_size;
	int m_id;
	Node * m_parent;
	std::vector<Node*> m_children;
	std::string m_name;
};

} // namespace zeug
