#include "searchTree.h"
#pragma once


class BalancedTree : public SearchTree
{
public:
	BalancedTree() : SearchTree() {};
	BalancedTree(const BalancedTree &copy) : SearchTree(copy) {};
	~BalancedTree() = default;

	using BinaryTree::addNode;
	using BinaryTree::deleteNodeByIndex;

	bool deleteNodeByKey(const int key, const int rootIndex = 0) override;

	BalancedTree copySubTree(const int nodeIndex = 0) const;
	BalancedTree& operator=(const BalancedTree& other);

	bool isSearchTree(const int nodeindex = 0) const;

private:

	bool addNode(Node* node, const int key) override;
	bool deleteNodeByIndex(Node* node) override;
	BalancedTree copySubTree(Node* subTreeRoot) const;
	Node* deleteNode(Node* node, const int key, bool& wasDeleted);
	Node* addNodeRec(Node* node, const int key);
	bool isSearchTree(Node* parent) const;
	Node* balanceTree(Node* node);
	Node* rotateRight(Node* parent);
	Node* rotateLeft(Node* parent);
	Node* rotateRightTwice(Node* parent);
	Node* rotateLeftTwice(Node* parent);
	Node* findNodeByKey(Node* subTreeRoot, const int key) const;
	int height(Node* node) const;
	int balance(Node* node) const;
	void newHeight(Node* node) const;
	Node* findMin(Node* node) const;
	Node* balanceMinSubtree(Node* node);
};

