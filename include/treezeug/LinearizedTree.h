#pragma once

#include <Tree.h>

#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>

#include <ConnectionMap.h>

class LinearizedTree
{
public:
	enum Algorithm
	{
		None,
		DepthFirst,
        BreadthFirst,
        OptimizedBreadthFirst
	};

	LinearizedTree();
	LinearizedTree(const Tree* tree, Algorithm strategy);

	void linearize();
	void clear();

	const Tree* tree() const;
	void setTree(const Tree* tree);

	void setAlgorithm(Algorithm strategy);

	unsigned size() const;
	int maxId() const;
	const Node* root() const;

	int indexOf(const Node* node) const;
    int indexOf(int id) const;
	const Node* at(int index) const;
	const Node* operator[](int index) const;
    const Node* getNode(int id) const;

	std::vector<const Node*>::const_iterator begin() const;
	std::vector<const Node*>::const_iterator end() const;

    const std::vector<std::pair<int, int>>& thresholds() const;
	void treeLayerRangesDo(std::function<void(int, int)> callback) const;
protected:
	const Tree* _tree;
	Algorithm _strategy;
	int _nextIndex;

	std::vector<const Node*> _nodes;
	std::unordered_map<const Node*, int> _indices;
    std::vector<std::pair<int, int>> _treeDepthTresholds;

	void linearizeDepthFirst();
	void linearizeBreadthFirst();
    void linearizeOptimizedBreadthFirst();

	void add(const Node* node);
};
