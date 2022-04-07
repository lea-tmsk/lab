#include "binaryTree.h"
#pragma once


class SearchTree : public BinaryTree
{
public:
	SearchTree() : BinaryTree() {};
	SearchTree(const SearchTree& copy) : BinaryTree(copy) {};
	~SearchTree() = default;

	int getMin(const int nodeIndex = 0) const override;
	int getMax(const int nodeIndex = 0) const override;
	bool addNode(const int key, const int nodeIndex = 0) override;
	bool deleteNodeByKey(const int key, const int nodeIndex = 0) override;
	bool deleteNodeByIndex(const int deleteIndex, const int nodeIndex = 0);
	int getIndexByKey(const int key, const int nodeIndex = 0) const;
	int getLevelByKey(const int key, const int nodeIndex = 0) const override;

	SearchTree& operator=(const SearchTree& other);

private:
	int getMin(Node* subTreeRoot) const override;
	int getMax(Node* subTreeRoot) const override;
	bool addNode(Node* node, const int key) override;
	bool deleteNodeByKey(Node* subTreeRoot, const int key);
	bool deleteNodeByIndex(Node* subTreeRoot, const int deleteIndex);
	int getIndexByKey(Node* subTreeRoot, const int key) const;
	int getLevelByKey(Node* subTreeRoot, const int key) const override;

	bool deleteRoot();
	bool deleteLeftBothChildren(Node* parent, Node* subTreeRoot);
	bool deleteRightBothChildren(Node* parent, Node* subTreeRoot);
	bool deleteLeftOneChild(Node* parent, Node* subTreeRoot);
	bool deleteRightOneChild(Node* parent, Node* subTreeRoot);
};

