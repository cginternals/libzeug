#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>

#include <signalzeug/ConnectionMap.h>

#include <treezeug/treezeug.h>
#include <treezeug/Tree.h>


namespace zeug
{

class TREEZEUG_API LinearizedTree
{
public:
    enum Algorithm
	{
		None
    ,   DepthFirst
    ,   BreadthFirst
    ,   OptimizedBreadthFirst
	};

public:
	LinearizedTree();
    LinearizedTree(const Tree * tree, Algorithm strategy);

    LinearizedTree* copy();

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
    void reverseTreeLayerRangesDo(std::function<void(int, int)> callback) const;
    void fullTreeLayerRangesDo(std::function<void(int, int)> callback) const;
    void fullReverseTreeLayerRangesDo(std::function<void(int, int)> callback) const;
protected:
	void linearizeDepthFirst();
	void linearizeBreadthFirst();
    void linearizeOptimizedBreadthFirst();

	void add(const Node* node);

protected:
	const Tree * m_tree;
	Algorithm m_strategy;
	int m_nextIndex;

	std::vector<const Node*> m_nodes;
	std::unordered_map<const Node*, int> m_indices;
    std::vector<std::pair<int, int>> m_treeDepthTresholds;

    LinearizedTree(const LinearizedTree& other);
};

} // namespace zeug
