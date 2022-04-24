#include "searchTree.h"
#pragma once


class BalancedTree : public SearchTree
{
public:
	BalancedTree() : SearchTree() {};
	BalancedTree(const BalancedTree &copy) : SearchTree(copy) {};
	~BalancedTree() = default;

	using BinaryTree::addNode;
	using BinaryTree::deleteNodeByKey;
	using BinaryTree::deleteNodeByIndex;

	BalancedTree copySubTree(const int nodeIndex = 0) const;
	BalancedTree& operator=(const BalancedTree& other);

	bool isSearchTree(const int nodeindex = 0) const;

private:
	bool addNode(Node* node, const int key, bool& unbalanced);

	bool addNode(Node* node, const int key) override;
	bool deleteNodeByKey(Node* subTreeRoot, const int key) override;
	bool deleteNodeByIndex(Node* subTreeRoot) override;
	BalancedTree copySubTree(Node* subTreeRoot) const;

	bool isSearchTree(Node* parent) const;
	void checkBalances(Node* subTreeRoot);
	bool balanceTree(Node* node);
	void rotateRight(Node* parent);
	void rotateLeft(Node* parent);
	void rotateRightTwice(Node* parent);
	void rotateLeftTwice(Node* parent);
};

