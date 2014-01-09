#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include <treezeug/treezeug.h>
#include <treezeug/AttributeMap.h>
#include <treezeug/Node.h>


namespace zeug
{

class TreeData;

class TREEZEUG_API Tree
{
public:
	Tree(const std::string& name);
	virtual ~Tree();

    Tree * copy() const;
    Tree * restrictTo(Node * newRoot) const;
    Tree * restrictTo(int id) const;

    const std::string& name() const;

	unsigned size() const;
	int maxId() const;
    unsigned depth() const;

    const Node* root() const;
    const Node* getNode(int id) const;
    const Node* getNodeByPath(const std::string& path, char separator = '/') const;

    void nodesDo(std::function<void(const Node*)> action) const;
    void nodesOrderedByDepthDo(std::function<void(const Node*)> action) const;
	void leavesDo(std::function<void(const Node*)> action) const;

    bool hasAttributeMap(const std::string & name) const;

    AttributeMap::Type attributeMapType(const std::string & name) const;
    const std::vector<std::string> & attributes() const;
protected:
    std::shared_ptr<TreeData> m_data;
    Node* m_root;

    Tree(const Tree& other);
    Tree(std::shared_ptr<TreeData> data);
};

} // namespace zeug
