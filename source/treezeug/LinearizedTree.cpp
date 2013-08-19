#include <LinearizedTree.h>

LinearizedTree::LinearizedTree()
: _tree(nullptr)
, _strategy(None)
, _nextIndex(0)
{
}

LinearizedTree::LinearizedTree(const Tree* tree, Algorithm strategy)
: _tree(tree)
, _strategy(strategy)
, _nodes(tree->size())
, _nextIndex(0)
{
	linearize();
}

const Tree* LinearizedTree::tree() const
{
	return _tree;
}

void LinearizedTree::setTree(const Tree* tree)
{
	if (_tree == tree) return;

	_tree = tree;
}

void LinearizedTree::setAlgorithm(Algorithm strategy)
{
	if (_strategy == strategy) return;

	_strategy = strategy;
}

unsigned LinearizedTree::size() const
{
	return _tree ? _tree->size() : 0;
}

int LinearizedTree::maxId() const
{
	return _tree ? _tree->maxId() : 0;
}

const Node* LinearizedTree::root() const
{
	return _tree ? _tree->root() : nullptr;
}

int LinearizedTree::indexOf(const Node* node) const
{
	if (!_indices.count(node))
	{
		return -1;
	}

	return _indices.at(node);
}

int LinearizedTree::indexOf(int id) const
{
    return indexOf(getNode(id));
}

const Node* LinearizedTree::at(int index) const
{
	return _nodes[index];
}

const Node* LinearizedTree::operator[](int index) const
{
	return _nodes[index];
}

const Node* LinearizedTree::getNode(int id) const
{
    return _tree->getNode(id);
}

void LinearizedTree::treeLayerRangesDo(std::function<void(int, int)> callback) const
{
	unsigned start = 0;
	for (unsigned i = 1; i < _treeDepthTresholds.size(); ++i)
	{
		unsigned end = _treeDepthTresholds[i]-1;

		callback(start, end);

		start = end+1;
	}
}

std::vector<const Node*>::const_iterator LinearizedTree::begin() const
{
	return _nodes.begin();
}

std::vector<const Node*>::const_iterator LinearizedTree::end() const
{
	return _nodes.end();
}

void LinearizedTree::linearize()
{
	clear();

	if (!_tree)
	{
		return;
	}

	switch (_strategy)
	{
	case DepthFirst:
		linearizeDepthFirst();
		break;
	case BreadthFirst:
		linearizeBreadthFirst();
		break;
	}
}

void LinearizedTree::clear()
{
	_nextIndex = 0;
	_nodes.clear();
	_indices.clear();
	_treeDepthTresholds.clear();

	if (_tree)
	{
		_nodes.resize(_tree->size());
		_treeDepthTresholds.reserve(_tree->depth()+1);
	}
}

void LinearizedTree::add(const Node* node)
{
	int index = _nextIndex++;

	_nodes[index] = node;
	_indices[node] = index;
}

void LinearizedTree::linearizeDepthFirst()
{
	_tree->nodesDo([this](const Node* node) { add(node); });
}

void LinearizedTree::linearizeBreadthFirst()
{
	_tree->nodesOrderedByDepthDo([this](const Node* node) {
		add(node);

		while (_treeDepthTresholds.size() <= node->depth())
		{
			_treeDepthTresholds.push_back(indexOf(node));
		}
	});

	_treeDepthTresholds.push_back(_tree->size());
}
