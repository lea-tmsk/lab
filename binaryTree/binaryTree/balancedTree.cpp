#include "balancedTree.h"
#include <iostream>

bool BalancedTree::addNode(Node* node, const int key)
{
	if (!node)
	{
		if (!m_root)
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
	if (addNodeRec(node, key))
	{
		return true;
	}
	return false;
}

BinaryTree::Node* BalancedTree::addNodeRec(Node* node, const int key)
{
	if (!node)
	{
		return new Node(key);
	}
	if (key == node->key)
	{
		return nullptr;
	}
	if (key < node->key)
	{
		node->leftChild = addNodeRec(node->leftChild, key);
	}
	else
	{
		node->rightChild = addNodeRec(node->rightChild, key);
	}
	if (node == m_root)
	{
		m_root = balanceTree(node);
		return m_root;
	}
	return balanceTree(node);
}

bool BalancedTree::deleteNodeByKey(const int key, const int rootIndex)
{
	bool wasDeleted = true;
	deleteNode(node(rootIndex), key, wasDeleted);
	if (wasDeleted)
	{
		return true;
	}
	return false;
}

BinaryTree::Node* BalancedTree::deleteNode(Node* node, const int key, bool& wasDeleted)
{
	if (!node)
	{
		wasDeleted = false;
		return nullptr;
	}
	
	if (key < node->key)
	{
		node->leftChild = deleteNode(node->leftChild, key, wasDeleted);
	}
	else if (key > node->key)
	{
		node->rightChild = deleteNode(node->rightChild, key, wasDeleted);
	}
	else
	{
		Node* leftChild = node->leftChild;
		Node* rightChild = node->rightChild;
		bool isRoot = (node == m_root ? true : false);
		if (isRoot && !leftChild && !rightChild)
		{
			m_root = nullptr;
			delete node;
			return nullptr;
		}
		delete node;
		if (!rightChild)
		{
			if (isRoot)
			{
				m_root = leftChild;
			}
			return leftChild;
		}
		Node* min = findMin(rightChild);
		min->rightChild = balanceMinSubtree(rightChild);
		min->leftChild = leftChild;
		if (isRoot)
		{
			m_root = balanceTree(min);
			return m_root;
		}
		return balanceTree(min);
	}
	if (node == m_root)
	{
		m_root = balanceTree(node);
		return m_root;
	}
	balanceTree(node);
}

bool BalancedTree::deleteNodeByIndex(Node* node)
{
	if (!node)
	{
		return false;
	}
	return deleteNodeByKey(node->key);
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

BinaryTree::Node* BalancedTree::balanceTree(Node* node)
{
	newHeight(node);
	int nodeBalance = balance(node);

	if (nodeBalance == -2)
	{
		if (balance(node->leftChild) < 1)
		{
			return rotateRight(node);
		}
		else
		{
			return rotateRightTwice(node);
		}
	}
	if (nodeBalance == 2)
	{
		Node* rightChild = node->rightChild;
		if (balance(node->rightChild) > -1)
		{
			return rotateLeft(node);
		}
		else
		{
			return rotateLeftTwice(node);
		}
	}
	return node;
}

BinaryTree::Node * BalancedTree::rotateRight(Node* parent)
{
	if (parent == nullptr)
	{
		return nullptr;
	}
	Node* child = parent->leftChild;

	parent->leftChild = child->rightChild;
	child->rightChild = parent;
	
	newHeight(parent);
	newHeight(child);

	return child;
}

BinaryTree::Node* BalancedTree::rotateLeft(Node* parent)
{
	if (parent == nullptr) 
	{
		return nullptr;
	}
	Node* child = parent->rightChild;

	parent->rightChild = child->leftChild;
	child->leftChild = parent;

	newHeight(parent);
	newHeight(child);
	
	return child;
}

BinaryTree::Node* BalancedTree::rotateRightTwice(Node* parent)
{
	parent->leftChild = rotateLeft(parent->leftChild);
	return rotateRight(parent);
}

BinaryTree::Node* BalancedTree::rotateLeftTwice(Node* parent)
{
	parent->rightChild = rotateRight(parent->rightChild);
	return rotateLeft(parent);
}

BinaryTree::Node* BalancedTree::findNodeByKey(Node* subTreeRoot, const int key) const
{
	if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	if (key == subTreeRoot->key)
	{
		return subTreeRoot;
	}
	if (key > subTreeRoot->key)
	{
		return findNodeByKey(subTreeRoot->rightChild, key);
	}
	if (key < subTreeRoot->key)
	{
		return findNodeByKey(subTreeRoot->leftChild, key);
	}
}

int BalancedTree::height(Node* node) const
{
	if (!node)
	{
		return 0;
	}
	return node->height;
}

int BalancedTree::balance(Node* node) const
{
	if (!node)
	{
		return 0;
	}
	return height(node->rightChild) - height(node->leftChild);
}

void BalancedTree::newHeight(Node* node) const
{
	int heightLeft = height(node->leftChild);
	int heightRight = height(node->rightChild);
	if (heightLeft > heightRight)
	{
		node->height = heightLeft + 1;
	}
	else
	{
		node->height = heightRight + 1;
	}
}

BinaryTree::Node* BalancedTree::findMin(Node* node) const
{
	if (!node->leftChild)
	{
		return node;
	}
	else
	{
		return findMin(node->leftChild);
	}
}

BinaryTree::Node* BalancedTree::balanceMinSubtree(Node* node)
{
	if (!node->leftChild)
	{
		return node->rightChild;
	}
	node->leftChild = balanceMinSubtree(node->leftChild);
	return balanceTree(node);
}

