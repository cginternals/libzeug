
#include <algorithm>
#include <utility>

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
: m_tree(tree->copy())
, m_strategy(strategy)
, m_nodes(tree ? tree->size() : 0)
, m_nextIndex(0)
{
	linearize();
}

LinearizedTree::LinearizedTree(const LinearizedTree& other)
: m_tree(other.m_tree->copy())
, m_strategy(other.m_strategy)
, m_nextIndex(other.m_nextIndex)
, m_nodes(other.m_nodes)
, m_indices(other.m_indices)
, m_treeDepthTresholds(other.m_treeDepthTresholds)
{
}

LinearizedTree::~LinearizedTree()
{
    delete m_tree;
}

LinearizedTree* LinearizedTree::copy()
{
    return new LinearizedTree(*this);
}

const Tree * LinearizedTree::tree() const
{
	return m_tree;
}

void LinearizedTree::setTree(const Tree * tree)
{
    delete m_tree;

    m_tree = tree ? tree->copy() : nullptr;
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

void LinearizedTree::reverseTreeLayerRangesDo(std::function<void(int, int)> callback) const
{
    if (m_strategy == BreadthFirst || m_strategy == OptimizedBreadthFirst)
    {
        std::vector<std::pair<int, int>> reverseThresholds(m_treeDepthTresholds.size());
        std::reverse_copy(m_treeDepthTresholds.begin(), m_treeDepthTresholds.end(), reverseThresholds.begin());
        for (const std::pair<int, int>& pair : reverseThresholds)
        {
            callback(pair.first, pair.second);
        }
    }
}

void LinearizedTree::fullTreeLayerRangesDo(std::function<void(int, int)> callback) const
{
    if (m_strategy == BreadthFirst || m_strategy == OptimizedBreadthFirst)
    {
        int last = -1;
        for (const std::pair<int, int>& pair : m_treeDepthTresholds)
        {
            if (pair.first > last + 1)
            {
               callback(last+1, pair.first-1);
            }

            callback(pair.first, pair.second);

            last = pair.second;
        }

        if (last + 1 < m_nodes.size())
        {
            callback(last+1, m_nodes.size()-1);
        }
    }
}

void LinearizedTree::fullReverseTreeLayerRangesDo(std::function<void(int, int)> callback) const
{
   if (m_strategy == BreadthFirst || m_strategy == OptimizedBreadthFirst)
   {
        std::vector<std::pair<int, int>> fullThresholds;

        fullTreeLayerRangesDo([&fullThresholds](int start, int end){
            fullThresholds.push_back(std::make_pair(start, end));
        });

       std::vector<std::pair<int, int>> reverseThresholds(fullThresholds.size());
       std::reverse_copy(fullThresholds.begin(), fullThresholds.end(), reverseThresholds.begin());
       for (const std::pair<int, int>& pair : reverseThresholds)
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
