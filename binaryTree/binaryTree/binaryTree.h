#pragma once
#include <vector>
#include <string>

class BinaryTree
{
protected:
	class Node
	{
	public:
		Node(const int key = 0,
			 int height = 1,
			 Node* leftChild = nullptr,
			 Node* rightChild = nullptr) :
			key(key),
			height(height),
			leftChild(leftChild),
			rightChild(rightChild)
		{}

		int getBalance()
		{
			if (leftChild && rightChild)
			{
				return rightChild->height - leftChild->height;
			}
			if (leftChild)
			{
				return -leftChild->height;
			}
			if (rightChild)
			{
				return rightChild->height;
			}
			return 0;
		}

		int getKey() const;
		int numberOfChildren() const;

		int key = 0;
		int height = 1;
		Node* leftChild = nullptr;
		Node* rightChild = nullptr;
	};

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& copy);
	virtual ~BinaryTree();

	bool addNode(const int key, const int nodeIndex = 0);
	bool isEmpty(const int nodeIndex = 0) const;
	bool isTreeBalanced(const int nodeIndex = 0) const;
	int numberOfNodes(const int nodeIndex = 0) const;
	int treeHeight(const int nodeIndex = 0) const;
	std::vector<int> treeKeysVector(const int nodeIndex = 0) const;
	BinaryTree copySubTree(const int nodeIndex) const;
	int getMin(const int nodeIndex = 0) const;
	int getMax(const int nodeIndex = 0) const;
	int keysSum(const int nodeIndex = 0) const;
	int getLevelByKey(const int key, const int nodeIndex = 0) const;
	int getIndexByKey(const int key, const int nodeIndex = 0) const;
	int getKeyByIndex(const int nodeIndex = 0) const;
	bool deleteNodeByIndex(const int deleteIndex, const int nodeIndex = 0);
	virtual bool deleteNodeByKey(const int key, const int nodeIndex = 0);
	void deleteTree(const int nodeIndex = 0);
	void deleteSubTrees(const int nodeIndex = 0);
	void printLevel(const int level, const int nodeIndex = 0) const;
	void printLeaves(const int nodeIndex = 0) const;
	void print() const;

	Node* findKey(const int key, const int nodeIndex = 0) const;
	BinaryTree& operator=(const BinaryTree& bt);

protected:
	virtual int getMin(Node* subTreeRoot) const;
	virtual int getMax(Node* subTreeRoot) const;
	virtual bool addNode(Node* subTreeRoot, const int key);
	virtual bool deleteNodeByKey(Node* subTreeRoot, const int key);
	virtual bool deleteNodeByIndex(Node* subTreeRoot);
	virtual int getLevelByKey(Node* subTreeRoot, const int key) const;

	bool addLeft(Node* subTreeRoot, const int key);
	bool addRight(Node* subTreeRoot, const int key);
	bool isEmpty(const Node* subTreeRoot) const;
	bool isTreeBalanced(Node* subTreeRoot) const;
	int numberOfNodes(const Node* subTreeRoot, int& count) const;
	int treeHeight(Node* subTreeRoot) const;
	std::vector<int> treeKeysVector(Node* subTreeRoot) const;
	BinaryTree copySubTree(const Node* subTreeRoot) const;
	int keysSum(Node* subTreeRoot) const;
	int getIndexByKey(Node* subTreeRoot, const int key) const;
	int getKeyByIndex(Node* subTreeRoot) const;
	void copyTree(const Node* subTreeRoot);
	void copyNodes(const Node* subTreeRoot, Node* copyRoot);
	void deleteTree(Node* subTreeRoot);
	void printLevel(Node* subTreeRoot, const int level, const int currentLevel) const;
	void printLeaves(Node* subTreeRoot) const;
	void printLeavesRec(Node* subTreeRoot) const;

	Node* findParent(Node* child) const;
	Node* findKey(Node* subTreeRoot, const int key) const;
	Node* node(const int nodeIndex) const;
	Node* node(const int subTreeRootIndex, const int nodeIndex) const;
	Node* node(Node* subTreeRoot, int nodeIndex) const;

	Node* m_root = nullptr;
};


