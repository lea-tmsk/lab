#include "balancedTree.h"

bool BalancedTree::addNode(Node* node, const int key)
{
	if (node == nullptr)
	{
		if (node == m_root)
		{
			m_root = new Node(key);
			return true;
		}
		return false;
	}
	if (findKey(node, key))
	{
		return false;
	}
	bool unbalanced = false;
	addNode(node, key, unbalanced);
	while (!isTreeBalanced())
	{
		checkBalances(m_root);
	}
	return true;
}

bool BalancedTree::addNode(Node* node, const int key, bool& unbalanced)
{
	if (key >= node->key)
	{
		if (!node->rightChild)
		{
			node->rightChild = new Node(key);
		}
		else
		{
			return addNode(node->rightChild, key, unbalanced);
		}
	}
	else
	{
		if (!node->leftChild)
		{
			node->leftChild = new Node(key);
		}
		else
		{
			return addNode(node->leftChild, key, unbalanced);
		}
	}
	return true;
}

bool BalancedTree::deleteNodeByKey(Node* subTreeRoot, const int key)
{
	return deleteNodeByIndex(findKey(subTreeRoot, key));
}

bool BalancedTree::deleteNodeByIndex(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}
	SearchTree::deleteNodeByIndex(subTreeRoot);
	if (!isEmpty())
	{
		while (!isTreeBalanced())
		{
			checkBalances(m_root);
		}
	}
	return true;
}

BalancedTree BalancedTree::copySubTree(const int nodeIndex) const
{
	return copySubTree(node(nodeIndex));
}

BalancedTree BalancedTree::copySubTree(Node* subTreeRoot) const
{
	if (subTreeRoot == nullptr)
	{
		return BalancedTree();
	}
	BalancedTree st;
	st.copyTree(subTreeRoot);
	return st;
}

BalancedTree& BalancedTree::operator=(const BalancedTree& other)
{
	if (this == &other)
	{
		return *this;
	}
	BinaryTree::operator=(other);
	return *this;
}

bool BalancedTree::isSearchTree(const int nodeindex) const
{
	if (m_root == nullptr)
	{
		return true;
	}
	return isSearchTree(node(nodeindex));
}

bool BalancedTree::isSearchTree(Node* parent) const
{
	if (parent == nullptr)
	{
		return true;
	}
	if (parent->leftChild)
	{
		isSearchTree(parent->leftChild);
		if (parent->leftChild->key >= parent->key)
		{
			return false;
		}
	}
	if (parent->rightChild)
	{
		isSearchTree(parent->rightChild);
		if (parent->rightChild->key < parent->key)
		{
			return false;
		}
	}
	return true;
}

void BalancedTree::checkBalances(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}
	
	int left = 0;
	int right = 0;
	if (subTreeRoot->leftChild)
	{
		checkBalances(subTreeRoot->leftChild);
		left = treeHeight(subTreeRoot->leftChild);
	}
	if (subTreeRoot->rightChild)
	{
		checkBalances(subTreeRoot->rightChild);
		right = treeHeight(subTreeRoot->rightChild);
	}
	subTreeRoot->balance = right - left;
	if (abs(subTreeRoot->balance) > 1)
	{
		balanceTree(subTreeRoot);
	}
}

bool BalancedTree::balanceTree(Node* node)
{
	if (node->balance < -1)
	{
		Node* leftChild = node->leftChild;
		if (leftChild->balance < 1)
		{
			rotateRight(node);
		}
		else
		{
			rotateRightTwice(node);
		}
	}
	if (node->balance > 1)
	{
		Node* rightChild = node->rightChild;
		if (rightChild->balance > -1)
		{
			rotateLeft(node);
		}
		else
		{
			rotateLeftTwice(node);
		}
	}
	return true;
}

void BalancedTree::rotateRight(Node* parent)
{
	if (parent == nullptr || !parent->leftChild)
	{
		return;
	}
	Node* child = parent->leftChild;
	Node* centralSubTree = child->rightChild;

	Node* grandparent = findParent(parent);
	if (grandparent)
	{
		if (grandparent->leftChild == parent)
		{
			grandparent->leftChild = child;
		}
		else
		{
			grandparent->rightChild = child;
		}
	}
	else
	{
		m_root = child;
	}
	child->rightChild = parent;
	parent->leftChild = centralSubTree;
}

void BalancedTree::rotateLeft(Node* parent)
{
	if (parent == nullptr || !parent->rightChild)
	{
		return;
	}
	Node* child = parent->rightChild;
	Node* centralSubTree = child->leftChild;

	Node* grandparent = findParent(parent);
	if (grandparent)
	{
		if (grandparent->leftChild == parent)
		{
			grandparent->leftChild = child;
		}
		else
		{
			grandparent->rightChild = child;
		}
	}
	else
	{
		m_root = child;
	}

	child->leftChild = parent;
	parent->rightChild = centralSubTree;
}

void BalancedTree::rotateRightTwice(Node* parent)
{
	rotateLeft(parent->leftChild);
	rotateRight(parent);
}

void BalancedTree::rotateLeftTwice(Node* parent)
{
	rotateRight(parent->rightChild);
	rotateLeft(parent);
}