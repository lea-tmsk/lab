#include "binaryTree.h"
#pragma once


class SearchTree : public BinaryTree
{
public:
	SearchTree() : BinaryTree() {};
	SearchTree(const SearchTree& copy) : BinaryTree(copy) {};
	~SearchTree() = default;

	using BinaryTree::getMin;
	using BinaryTree::getMax;
	using BinaryTree::addNode;
	using BinaryTree::deleteNodeByKey;
	using BinaryTree::deleteNodeByIndex;
	using BinaryTree::getIndexByKey;
	using BinaryTree::getLevelByKey;

	SearchTree copySubTree(const int nodeIndex = 0) const;
	SearchTree& operator=(const SearchTree& other);

private:
	int getMin(Node* subTreeRoot) const override;
	int getMax(Node* subTreeRoot) const override;
	bool addNode(Node* node, const int key) override;
	bool deleteNodeByKey(Node* subTreeRoot, const int key) override;
	bool deleteNodeByIndex(Node* subTreeRoot) override;
	int getLevelByKey(Node* subTreeRoot, const int key) const override;
	SearchTree copySubTree(Node* subTreeRoot) const;

	bool deleteRoot();
	bool deleteLeftBothChildren(Node* parent);
	bool deleteRightBothChildren(Node* parent);
	bool deleteLeftOneChild(Node* parent);
	bool deleteRightOneChild(Node* parent);
};

