#pragma once
#include <vector>
#include <string>

class BinaryTree
{
public:
	class Node
	{
	public:
		Node(const int key = 0, Node* leftChild = nullptr, Node* rightChild = nullptr) :
			key(key),
			leftChild(leftChild),
			rightChild(rightChild)
		{}

		int getKey() const;
		int numberOfChildren() const;

		int key = 0;
		Node* leftChild = nullptr;
		Node* rightChild = nullptr;
	};

	BinaryTree() = default;
	BinaryTree(const BinaryTree& copy);
	~BinaryTree();

	bool addNode(const int key, const int nodeIndex = 0);
	bool addLeft(const int key, const int nodeIndex = 0);
	bool addRight(const int key, const int nodeIndex = 0);
	bool isEmpty(const int nodeIndex = 0) const;
	bool isTreeBalanced(const int nodeIndex = 0) const;
	int numberOfNodes(const int nodeIndex = 0) const;
	int treeHeight(const int nodeIndex = 0) const;
	std::vector<int> treeKeysVector(const int nodeIndex = 0) const;
	BinaryTree copySubTree(const int nodeIndex) const;
	int minKey(const int nodeIndex = 0) const;
	int maxKey(const int nodeIndex = 0) const;
	int keysSum(const int nodeIndex = 0) const;
	int findKeyLevel(const int key, const int nodeIndex = 0) const;
	int getIndexByKey(const int key, const int nodeIndex = 0) const;
	int getKeyByIndex(const int nodeIndex = 0) const;
	bool deleteNode(const int nodeIndex = 0);
	bool deleteNodeKey(const int key, const int nodeIndex = 0);
	void deleteTree(const int nodeIndex = 0);
	void deleteSubTrees(const int nodeIndex = 0);
	void printLevel(const int level, const int nodeIndex = 0) const;
	void printLeaves(const int nodeIndex = 0) const;
	void print() const;

	Node* findKey(const int key, const int nodeIndex = 0) const;
	void operator=(const BinaryTree& bt);

private:
	bool addNode(Node* subTreeRoot, const int key);
	bool addLeft(Node* subTreeRoot, const int key);
	bool addRight(Node* subTreeRoot, const int key);
	bool isEmpty(const Node* subTreeRoot) const;
	bool isTreeBalanced(Node* subTreeRoot) const;
	int numberOfNodes(const Node* subTreeRoot, int& count) const;
	int treeHeight(Node* subTreeRoot) const;
	std::vector<int> treeKeysVector(Node* subTreeRoot) const;
	BinaryTree copySubTree(const Node* subTreeRoot) const;
	int minKey(Node* subTreeRoot) const;
	int maxKey(Node* subTreeRoot) const;
	int keysSum(Node* subTreeRoot) const;
	int findKeyLevel(Node* subTreeRoot, const int key) const;
	int getIndexByKey(Node* subTreeRoot, const int key) const;
	int getKeyByIndex(Node* subTreeRoot) const;
	void copyTree(const Node* subTreeRoot);
	void copyNodes(const Node* subTreeRoot, Node* copyRoot);
	bool deleteNode(Node* subTreeRoot);
	void deleteTree(Node* subTreeRoot);
	void printLevel(Node* subTreeRoot, const int level) const;
	void printLeaves(Node* subTreeRoot) const;
	void printLeavesRec(Node* subTreeRoot) const;

	Node* findParent(Node* child) const;
	Node* findKey(Node* subTreeRoot, const int key) const;
	Node* node(const int nodeIndex) const;
	Node* node(const int subTreeRootIndex, const int nodeIndex) const;
	Node* node(Node* subTreeRoot, int nodeIndex) const;

	Node* m_root = nullptr;
};


