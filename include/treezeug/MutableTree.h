#pragma once

#include <functional>
#include <string>
#include <memory>

#include <treeimportzeug/treeimportzeug.h>

#include <treezeug/Tree.h>

namespace zeug
{

class TREEIMPORTZEUG_API MutableTree : public Tree
{
public:
    MutableTree(const std::string& name);
    virtual ~MutableTree();

    Node* root();
    Node* getNode(int id);
    Node* getNodeByPath(const std::string& path, char separator = '/');
    void setRoot(Node* node, int id = 0);

    void setName(const std::string& name);

    void nodesDo(std::function<void(Node*)> action);
    void nodesOrderedByDepthDo(std::function<void(Node*)> action);
    void leavesDo(std::function<void(Node*)> action);

	void addAttributeMap(const std::string & name, AttributeMap::Type type);

    void renormalizeAttributesForLeaves();
    void renormalizeAttributeForLeaves(const std::string& attribute);
protected:
    MutableTree(const Tree& other);
    MutableTree(std::shared_ptr<TreeData> data);
};

} // namespace zeug
