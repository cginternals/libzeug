#pragma once

#include <string>
#include <unordered_map>

namespace zeug {

class Node;
class Attribute;
class AttributeMap;

class TreeData
{
    friend class Tree;
public:
    TreeData(const std::string& name);
    ~TreeData();

    void setRoot(Node* node, int id);

    void registerNode(Node * node, bool silent = false);
    void deregisterNode(Node * node);

    bool hasAttributeMap(const std::string & name) const;
    void setAttribute(
        const Node * node
    ,   const std::string & name
    ,   double value);

    void setAttribute(
        const Node * node
    ,   const std::string & name
    ,   const std::string & value);

    const Attribute * attribute(const Node * node, const std::string & name) const;
protected:
    std::string m_name;
    Node * m_root;

    std::unordered_map<int, Node*> m_idMap;

    int m_nextId;
    unsigned m_depth;

    std::unordered_map<std::string, AttributeMap*> m_attributeMaps;
    std::vector<std::string> m_attributes;
};

} // namespace zeug
