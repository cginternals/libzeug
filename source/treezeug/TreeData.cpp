#include <algorithm>
#include <queue>
#include <iostream>
#include <sstream>

#include "TreeData.h"

#include <treezeug/Node.h>
#include <treezeug/AttributeMap.h>
#include <treezeug/Attribute.h>

namespace zeug
{

TreeData::TreeData(const std::string & name)
:   m_name(name)
,   m_root(new Node())
,   m_nextId(0)
,   m_depth(0)
{
    registerNode(m_root, true);
}

TreeData::~TreeData()
{
    delete m_root;

    for (const std::pair<std::string, AttributeMap*> & pair : m_attributeMaps)
    {
        delete pair.second;
    }
}

bool TreeData::hasAttributeMap(const std::string & name) const
{
    return m_attributeMaps.count(name) > 0;
}

void TreeData::setAttribute(const Node * node, const std::string & name, double value)
{
    if (!hasAttributeMap(name))
        return;

    m_attributeMaps[name]->addAttribute(node, value);
}

void TreeData::setAttribute(const Node * node, const std::string & name, const std::string & value)
{
    if (!m_attributeMaps.count(name))
        return;

    AttributeMap * map = m_attributeMaps[name];
    if (map)
        map->addAttribute(node, value);
}

const Attribute * TreeData::attribute(const Node * node, const std::string & name) const
{
    if (!m_attributeMaps.count(name))
        return nullptr;

    return m_attributeMaps.at(name)->attributeFor(node);
}

void TreeData::registerNode(Node * node, bool silent)
{
    node->m_data = this;

    if (node->m_id >= 0)
    {
        m_nextId = std::max(node->m_id + 1, m_nextId+1);
    }
    else
    {
        node->m_id = m_nextId;

        m_nextId++;
    }

    if (m_idMap.count(node->m_id))
    {
        if (!silent)
        {
            std::cout << "Replace node " << node->m_id << std::endl;
        }

        m_idMap[node->m_id]->reparentChildrenTo(node);

        delete m_idMap[node->m_id];
    }

    m_depth = std::max(m_depth, node->depth());

    m_idMap[node->m_id] = node;
}

void TreeData::deregisterNode(Node * node)
{
    if (m_root == node)
        m_root = nullptr;

    node->m_data = nullptr;

    m_idMap.erase(node->m_id);
}

void TreeData::setRoot(Node * node, int id)
{
    node->m_id = id;
    registerNode(node, true);
    node->m_parent = nullptr;
    m_root = node;
}

} // namespace zeug
