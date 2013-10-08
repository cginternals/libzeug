
#include <algorithm>

#include <treezeug/LinearizedTree.h>


namespace zeug
{

LinearizedTree::LinearizedTree()
:   m_tree(nullptr)
,   m_strategy(None)
,   m_nextIndex(0)
{
}

LinearizedTree::LinearizedTree(const Tree * tree, Algorithm strategy)
: m_tree(tree)
, m_strategy(strategy)
, m_nodes(tree ? tree->size() : 0)
, m_nextIndex(0)
{
	linearize();
}

const Tree * LinearizedTree::tree() const
{
	return m_tree;
}

void LinearizedTree::setTree(const Tree * tree)
{
	if (m_tree == tree) return;

	m_tree = tree;
}

void LinearizedTree::setAlgorithm(Algorithm strategy)
{
	if (m_strategy == strategy) return;

	m_strategy = strategy;
}

unsigned LinearizedTree::size() const
{
	return m_tree ? m_tree->size() : 0;
}

int LinearizedTree::maxId() const
{
    return m_tree ? m_tree->maxId() : -1;
}

const Node* LinearizedTree::root() const
{
	return m_tree ? m_tree->root() : nullptr;
}

int LinearizedTree::indexOf(const Node* node) const
{
	if (!m_indices.count(node))
	{
		return -1;
	}

	return m_indices.at(node);
}

int LinearizedTree::indexOf(int id) const
{
    return indexOf(getNode(id));
}

const Node * LinearizedTree::at(int index) const
{
	return m_nodes[index];
}

const Node * LinearizedTree::operator[](int index) const
{
	return m_nodes[index];
}

const Node * LinearizedTree::getNode(int id) const
{
    return m_tree->getNode(id);
}

const std::vector<std::pair<int, int>> & LinearizedTree::thresholds() const
{
    return m_treeDepthTresholds;
}

void LinearizedTree::treeLayerRangesDo(std::function<void(int, int)> callback) const
{
    if (m_strategy == BreadthFirst || m_strategy == OptimizedBreadthFirst)
    {
        for (const std::pair<int, int>& pair : m_treeDepthTresholds)
        {
            callback(pair.first, pair.second);
        }
    }
}

std::vector<const Node*>::const_iterator LinearizedTree::begin() const
{
	return m_nodes.begin();
}

std::vector<const Node*>::const_iterator LinearizedTree::end() const
{
	return m_nodes.end();
}

void LinearizedTree::linearize()
{
	clear();

	if (!m_tree)
		return;

	switch (m_strategy)
	{
	case DepthFirst:
		linearizeDepthFirst();
		break;
	case BreadthFirst:
		linearizeBreadthFirst();
		break;
    case OptimizedBreadthFirst:
        linearizeOptimizedBreadthFirst();
        break;
    }
}

void LinearizedTree::clear()
{
	m_nextIndex = 0;
	m_nodes.clear();
	m_indices.clear();
    m_treeDepthTresholds.clear();

	if (m_tree)
	{
        m_nodes.resize(m_tree->size());
	}
}

void LinearizedTree::add(const Node * node)
{
	int index = m_nextIndex++;

	m_nodes[index] = node;
	m_indices[node] = index;
}

void LinearizedTree::linearizeDepthFirst()
{
	m_tree->nodesDo([this](const Node* node) { add(node); });
}

void LinearizedTree::linearizeBreadthFirst()
{
	m_tree->nodesOrderedByDepthDo([this](const Node * node) {
		add(node);

        if (m_treeDepthTresholds.size() < node->depth()+1)
		{
            m_treeDepthTresholds.emplace_back(indexOf(node), indexOf(node));
		}
        else
        {
            m_treeDepthTresholds.back().second = indexOf(node);
        }
    });
}

void LinearizedTree::linearizeOptimizedBreadthFirst()
{
    std::vector<const Node*> currentLevel;

    m_tree->nodesOrderedByDepthDo([this, &currentLevel](const Node * node)
    {
        if (!currentLevel.empty() && node->depth() > currentLevel.back()->depth())
        {
            std::sort(currentLevel.begin(), currentLevel.end(), [](const Node* node1, const Node* node2) {
                return (node1->isLeaf() ? 0 : 1) < (node2->isLeaf() ? 0 : 1);
            });

            for (const Node* child : currentLevel)
            {
                add(child);
            }

            for (const Node* child : currentLevel)
            {
                if (child->isLeaf())
                {
                    continue;
                }

                m_treeDepthTresholds.emplace_back(indexOf(child), indexOf(currentLevel.back()));
                break;
            }

            currentLevel.clear();
        }

        currentLevel.push_back(node);
    });

    // only add the remaining nodes because they are all leafs
    for (const Node* child : currentLevel)
    {
        add(child);
    }
}

} // namespace zeug
