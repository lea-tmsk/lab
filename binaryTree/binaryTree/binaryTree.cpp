#include "binaryTree.h"
#include <vector>
#include <iostream>
#include <cassert>

int BinaryTree::Node::numberOfChildren() const
{
	int count = 0;
	if (leftChild)
	{
		count++;
	}
	if (rightChild)
	{
		count++;
	}
	return count;
}

int BinaryTree::Node::getKey() const
{
	return key;
}

BinaryTree::BinaryTree(const BinaryTree& copy)
{
	copyTree(copy.m_root);
}

BinaryTree::~BinaryTree()
{
	deleteTree(m_root);
}

bool BinaryTree::addNode(const int key, const int nodeIndex)
{
	return addNode(node(nodeIndex), key);
}

bool BinaryTree::addNode(Node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr)
	{
		if (m_root == nullptr)
		{
			m_root = new Node(key);
			return true;
		}
		return false;
	}

	if (!subTreeRoot->leftChild)
	{
		subTreeRoot->leftChild = new Node(key);
		return true;
	}
	
	if (!subTreeRoot->rightChild)
	{
		subTreeRoot->rightChild = new Node(key);
		return true;
	}

	if (rand() % 2)
	{
		addNode(subTreeRoot->leftChild, key);
		return true;
	}
	else
	{
		addNode(subTreeRoot->rightChild, key);
		return true;
	}
	
	return false;
}

bool BinaryTree::addLeft(const int key, const int nodeIndex)
{
	return addLeft(node(nodeIndex), key);
}

bool BinaryTree::addLeft(Node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}
	if (!subTreeRoot->leftChild)
	{
		subTreeRoot->leftChild = new Node(key);
		return true;
	}
	return false;
}

bool BinaryTree::addRight(const int key, const int nodeIndex)
{
	return addRight(node(nodeIndex), key);
}

bool BinaryTree::addRight(Node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}
	if (!subTreeRoot->rightChild)
	{
		subTreeRoot->rightChild = new Node(key);
		return true;
	}
	return false;
}

bool BinaryTree::isEmpty(const int nodeIndex) const
{
	return isEmpty(node(nodeIndex));
}

bool BinaryTree::isEmpty(const Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
	{
		return true;
	}
	return false;
}

int BinaryTree::numberOfNodes(const int nodeIndex) const
{
	int count = 1;
	return numberOfNodes(node(nodeIndex), count);
}

bool BinaryTree::isTreeBalanced(const int nodeIndex) const
{
	return isTreeBalanced(node(nodeIndex));
}

bool BinaryTree::isTreeBalanced(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}

	bool leftSubTreeBalanced = false, rightSubTreeBalanced = false;

	if (subTreeRoot->leftChild)
	{
		if (!isTreeBalanced(subTreeRoot->leftChild))
		{
			return false;
		}
	}

	if (subTreeRoot->rightChild)
	{
		if (!isTreeBalanced(subTreeRoot->rightChild))
		{
			return false;
		}
	}

	int heightDifference = treeHeight(subTreeRoot->leftChild) - treeHeight(subTreeRoot->rightChild);

	if (heightDifference >= -1 && heightDifference <= 1)
	{
		return true;
	}

	return false;
}

int BinaryTree::numberOfNodes(const Node* subTreeRoot, int &count) const
{
	if (subTreeRoot == nullptr)
	{
		return -1;
	}

	if (subTreeRoot->leftChild)
	{
		count++;
		numberOfNodes(subTreeRoot->leftChild, count);
	}

	if (subTreeRoot->rightChild)
	{
		count++;
		numberOfNodes(subTreeRoot->rightChild, count);
	}

	return count;
}

int BinaryTree::treeHeight(const int nodeIndex) const
{
	return treeHeight(node(nodeIndex));
}

int BinaryTree::treeHeight(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
	{
		return 0;
	}
	
	int height = 0;
	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		height++;
		currentLevelNodes.swap(nextLevelNodes);
	}

	return height;
}

std::vector<int> BinaryTree::treeKeysVector(const int nodeIndex) const
{
	return treeKeysVector(node(nodeIndex));
}

std::vector<int> BinaryTree::treeKeysVector(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
	{
		return std::vector<int>();
	}

	std::vector<int> keys;
	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	keys.push_back(subTreeRoot->key);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				keys.push_back(node->leftChild->key);
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				keys.push_back(node->rightChild->key);
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}

	return keys;
}

BinaryTree BinaryTree::copySubTree(const int nodeIndex) const
{
	return copySubTree(node(nodeIndex));
}

BinaryTree BinaryTree::copySubTree(const Node* subTreeRoot) const
{
	BinaryTree bt;
	bt.copyTree(subTreeRoot);
	return bt;
}

int BinaryTree::minKey(const int nodeIndex) const
{
	return minKey(node(nodeIndex));
}

int BinaryTree::minKey(Node* subTreeRoot) const
{
	assert(subTreeRoot != nullptr && "minKey: subTreeRoot == nullptr");

	int min = subTreeRoot->key;
	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				if (node->leftChild->key < min)
				{
					min = node->leftChild->key;
				}
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				if (node->rightChild->key < min)
				{
					min = node->rightChild->key;
				}
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}

	return min;
}

int BinaryTree::maxKey(const int nodeIndex) const
{
	return maxKey(node(nodeIndex));
}

int BinaryTree::maxKey(Node* subTreeRoot) const
{
	assert(subTreeRoot != nullptr && "maxKey: subTreeRoot == nullptr");

	int max = subTreeRoot->key;
	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				if (node->leftChild->key > max)
				{
					max = node->leftChild->key;
				}
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				if (node->rightChild->key > max)
				{
					max = node->rightChild->key;
				}
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}

	return max;
}

int BinaryTree::keysSum(const int nodeIndex) const
{
	return keysSum(node(nodeIndex));
}

int BinaryTree::keysSum(Node* subTreeRoot) const
{
	assert(subTreeRoot != nullptr && "keysSum: subTreeRoot == nullptr");

	int sum = subTreeRoot->key;
	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				sum += node->leftChild->key;
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				sum += node->rightChild->key;
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}

	return sum;
}

int BinaryTree::findKeyLevel(const int key, const int nodeIndex) const
{
	return findKeyLevel(node(nodeIndex), key);
}

int BinaryTree::findKeyLevel(Node* subTreeRoot, const int key) const
{
	if (subTreeRoot == nullptr)
	{
		return -1;
	}
	int level = 1;
	if (subTreeRoot->key == key)
	{
		return level;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		level++;
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				if (node->leftChild->key == key)
				{
					return level;
				}
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				if (node->rightChild->key == key)
				{
					return level;
				}
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
	return -1;
}

void BinaryTree::copyTree(const Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}

	if (m_root)
	{
		deleteTree(m_root);
	}

	m_root = new Node(subTreeRoot->key);

	if (subTreeRoot->numberOfChildren() > 0)
	{
		copyNodes(subTreeRoot, m_root);
	}
}

void BinaryTree::copyNodes(const Node* subTreeRoot, Node* copyRoot)
{
	if (subTreeRoot == nullptr || copyRoot == nullptr)
	{
		return;
	}
	
	if (subTreeRoot->leftChild)
	{
		addLeft(copyRoot, subTreeRoot->leftChild->key);
		copyNodes(subTreeRoot->leftChild, copyRoot->leftChild);
	}

	if (subTreeRoot->rightChild)
	{
		addRight(copyRoot, subTreeRoot->rightChild->key);
		copyNodes(subTreeRoot->rightChild, copyRoot->rightChild);
	}
}

bool BinaryTree::deleteNode(const int nodeIndex)
{
	return deleteNode(node(nodeIndex));
}

bool BinaryTree::deleteNode(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}

	if (subTreeRoot == m_root)
	{
		if (subTreeRoot->leftChild)
		{
			m_root = subTreeRoot->leftChild;
			if (subTreeRoot->rightChild)
			{
				Node* temp = subTreeRoot->leftChild;
				while (temp->leftChild)
				{
					temp = temp->leftChild;
				}
				temp->leftChild = subTreeRoot->rightChild;
			}
			delete subTreeRoot;
			return true;
		}
		if (subTreeRoot->rightChild)
		{
			m_root = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}

	if (!subTreeRoot->rightChild && !subTreeRoot->leftChild)
	{
		Node* parent = findParent(subTreeRoot);
		if (parent)
		{
			if (parent->leftChild == subTreeRoot)
			{
				parent->leftChild = nullptr;
			}
			else
			{
				parent->rightChild = nullptr;
			}
		}
		delete subTreeRoot;
		return true;
	}

	if (subTreeRoot->rightChild && subTreeRoot->leftChild)
	{
		Node* parent = findParent(subTreeRoot);
		if (parent->leftChild == subTreeRoot)
		{
			parent->leftChild = subTreeRoot->leftChild;
			Node* temp = m_root;
			while (temp->leftChild)
			{
				temp = temp->leftChild;
			}
			temp->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			parent->rightChild = subTreeRoot->leftChild;
			Node* temp = m_root;
			while (temp->leftChild)
			{
				temp = temp->leftChild;
			}
			temp->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}

	if (subTreeRoot->leftChild)
	{
		Node* parent = findParent(subTreeRoot);
		if (parent->leftChild == subTreeRoot)
		{
			parent->leftChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			parent->rightChild = subTreeRoot->leftChild;
			delete subTreeRoot;
			return true;
		}
	}

	if (subTreeRoot->rightChild)
	{
		Node* parent = findParent(subTreeRoot);
		if (parent->leftChild == subTreeRoot)
		{
			parent->leftChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
		else
		{
			parent->rightChild = subTreeRoot->rightChild;
			delete subTreeRoot;
			return true;
		}
	}

	return false;
}

bool BinaryTree::deleteNodeKey(const int key, const int nodeIndex)
{
	return deleteNode(findKey(key, nodeIndex));
}

void BinaryTree::deleteTree(const int nodeIndex)
{
	deleteTree(node(nodeIndex));
}

int BinaryTree::getKeyByIndex(const int nodeIndex) const
{
	return getKeyByIndex(node(nodeIndex));
}

int BinaryTree::getKeyByIndex(Node* subTreeRoot) const
{
	return subTreeRoot->key;
}

void BinaryTree::deleteTree(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}

	if (subTreeRoot->leftChild)
	{
		deleteTree(subTreeRoot->leftChild);
	}

	if (subTreeRoot->rightChild)
	{
		deleteTree(subTreeRoot->rightChild);
	}

	delete subTreeRoot;
}

void BinaryTree::deleteSubTrees(const int nodeIndex)
{
	if (node(nodeIndex)->rightChild)
	{
		deleteTree(node(nodeIndex)->leftChild);
		node(nodeIndex)->rightChild = nullptr;
	}
	if (node(nodeIndex)->leftChild)
	{
		deleteTree(node(nodeIndex)->rightChild);
		node(nodeIndex)->leftChild = nullptr;
	}
}

void BinaryTree::printLevel(const int level, const int nodeIndex) const
{
	printLevel(node(nodeIndex), level);
}

void BinaryTree::printLevel(Node* subTreeRoot, const int level, const int currentLevel) const
{
	using std::cout;
	using std::endl;

	if (subTreeRoot == nullptr && subTreeRoot == m_root)
	{
		cout << "\nTree is empty" << endl;
	}

	int noLeftChild = 0, noRightChild = 0;

	if (currentLevel == level)
	{
		cout << subTreeRoot->key << "    ";
	}

	else if (currentLevel < level)
	{
		if (subTreeRoot->leftChild)
		{
			printLevel(subTreeRoot->leftChild, level, currentLevel + 1);
		}
		else
		{
			for (int i = 0; i < pow(2, noLeftChild); i++)
			cout << "x    ";
			noLeftChild++;
		}
		if (subTreeRoot->rightChild)
		{
			printLevel(subTreeRoot->rightChild, currentLevel + 1);
		}
		else
		{
			for (int i = 0; i < pow(2, noRightChild); i++)
			cout << "x    ";
			noRightChild++;
		}

	}
}

void BinaryTree::printLeaves(const int nodeIndex) const
{
	printLeaves(node(nodeIndex));
}

void BinaryTree::printLeaves(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
	{
		std::cout << "Tree is empty";
		return;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				nextLevelNodes.push_back(node->rightChild);
			}

			if (!node->leftChild && !node->rightChild)
			{
				std::cout << node->key << " ";
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
}

void BinaryTree::print() const
{
	int height = treeHeight();
	for (int i = 0; i < height; i++)
	{
		printLevel(i);
		std::cout << std::endl;
	}
}

BinaryTree::Node* BinaryTree::findParent(Node* child) const
{
	if (child == nullptr || child == m_root)
	{
		return nullptr;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(m_root);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				if (node->leftChild == child)
				{
					return node;
				}
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				if (node->rightChild == child)
				{
					return node;
				}
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
	return nullptr;
}

BinaryTree::Node* BinaryTree::findKey(const int key, const int nodeIndex) const
{
	return findKey(node(nodeIndex), key);
}

BinaryTree::Node* BinaryTree::findKey(Node* subTreeRoot, const int key) const
{
	if (subTreeRoot->key == key)
	{
		return subTreeRoot;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				if (node->leftChild->key == key)
				{
					return node->leftChild;
				}
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				if (node->rightChild->key == key)
				{
					return node->rightChild;
				}
				nextLevelNodes.push_back(node->rightChild);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}

	return nullptr;
}

void BinaryTree::operator=(const BinaryTree& bt)
{
	copyTree(bt.m_root);
}

BinaryTree::Node* BinaryTree::node(const int nodeIndex) const
{
	return node(m_root, nodeIndex);
}

BinaryTree::Node* BinaryTree::node(const int subTreeRootIndex, const int nodeIndex) const
{
	return node(node(subTreeRootIndex), nodeIndex);
}

BinaryTree::Node* BinaryTree::node(Node* subTreeRoot, int nodeIndex) const
{
	if (nodeIndex == 0)
	{
		return subTreeRoot;
	}
	if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	std::vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() && nodeIndex >= currentLevelNodes.size())
	{
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				nextLevelNodes.push_back(node->leftChild);
			}

			if (node->rightChild)
			{
				nextLevelNodes.push_back(node->rightChild);
			}
		}

		nodeIndex -= currentLevelNodes.size();
		currentLevelNodes.swap(nextLevelNodes);
	}

	if (!currentLevelNodes.size())
	{
		return nullptr;
	}
	return currentLevelNodes[nodeIndex];
}


