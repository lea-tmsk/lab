#include "searchTree.h"
#include <cassert>

int SearchTree::getMin(Node* subTreeRoot) const
{
	assert(subTreeRoot != nullptr && "getMin: subTreeRoot was nullptr");
	Node* temp = subTreeRoot;
	while (temp->leftChild)
	{
		temp = temp->leftChild;
	}
	return temp->getKey();
}

int SearchTree::getMax(Node* subTreeRoot) const
{
	assert(subTreeRoot != nullptr && "getMax: subTreeRoot was nullptr");
	Node* temp = subTreeRoot;
	while (temp->rightChild)
	{
		temp = temp->rightChild;
	}
	return temp->getKey();
}

bool SearchTree::addNode(Node* node, const int key)
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
	Node* temp = m_root;
	while (true)
	{
		while (key < temp->getKey())
		{
			if (temp->leftChild)
			{
				temp = temp->leftChild;
			}
			else if (key < temp->getKey())
			{
				temp->leftChild = new Node(key);
				return true;
			}
		}

		while (key >= temp->getKey())
		{
			if (temp->rightChild)
			{
				temp = temp->rightChild;
			}
			else if (key >= temp->getKey())
			{
				temp->rightChild = new Node(key);
				return true;
			}
		}
	}
	return false;
}

bool SearchTree::deleteNodeByKey(Node* subTreeRoot, const int key)
{
	return deleteNodeByIndex(getIndexByKey(subTreeRoot, key));
}

bool SearchTree::deleteNodeByIndex(Node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}

	if (subTreeRoot == nullptr)
	{
		return false;
	}

	if (subTreeRoot == m_root)
	{
		return deleteRoot();
	}

	Node* parent = findParent(subTreeRoot);

	if (!subTreeRoot->numberOfChildren())
	{
		if (parent->leftChild == subTreeRoot)
		{
			parent->leftChild = nullptr;
		}
		else
		{
			parent->rightChild = nullptr;
		}
		delete subTreeRoot;
		return true;
	}

	if (subTreeRoot->numberOfChildren() == 2)
	{
		if (parent->leftChild == subTreeRoot)
		{
			return deleteLeftBothChildren(parent);
		}
		else
		{
			return deleteRightBothChildren(parent);
		}
	}

	if (parent->leftChild == subTreeRoot)
	{
		return deleteLeftOneChild(parent);
	}

	if (parent->rightChild == subTreeRoot)
	{
		return deleteRightOneChild(parent);
	}
	return false;
}

int SearchTree::getLevelByKey(Node* subTreeRoot, const int key) const
{
	if (subTreeRoot == nullptr)
	{
		return -1;
	}
	Node* temp = subTreeRoot;
	int level = 1;
	while (key < temp->getKey() && temp->leftChild)
	{
		temp = temp->leftChild;
		level++;
	}

	while (key > temp->getKey() && temp->rightChild)
	{
		temp = temp->rightChild;
		level++;
	}

	if (key == temp->getKey())
	{
		return level;
	}

	return -1;
}

bool SearchTree::deleteRoot()
{
	Node* temp = m_root;

	if (temp->numberOfChildren() == 1)
	{
		if (temp->leftChild)
		{
			m_root = temp->leftChild;
		}
		else
		{
			m_root = temp->rightChild;
		}
		delete temp;
		return true;
	}

	if (!temp->numberOfChildren())
	{
		m_root = nullptr;
		delete temp;
		return true;
	}

	m_root = temp->rightChild;
	Node* place = m_root;

	while (place->leftChild)
	{
		place = place->leftChild;
	}

	place->leftChild = temp->leftChild;
	delete temp;
	return true;
}

bool SearchTree::deleteLeftBothChildren(Node* parent)
{
	Node* temp = parent->leftChild;
	parent->leftChild = temp->rightChild;
	Node* place = parent;

	while (place->leftChild)
	{
		place = place->leftChild;
	}

	place->leftChild = temp->leftChild;
	delete temp;
	return true;
}

bool SearchTree::deleteRightBothChildren(Node* parent)
{
	Node* temp = parent->rightChild;
	parent->rightChild = temp->leftChild;
	Node* place = parent;

	while (place->rightChild)
	{
		place = place->rightChild;
	}

	place->rightChild = temp->rightChild;
	delete temp;
	return true;
}

bool SearchTree::deleteLeftOneChild(Node* parent)
{
	Node* temp = parent->leftChild;

	if (temp->leftChild)
	{
		parent->leftChild = temp->leftChild;
	}
	else
	{
		parent->leftChild = temp->rightChild;
	}
	delete temp;
	return true;
}

bool SearchTree::deleteRightOneChild(Node* parent)
{
	Node* temp = parent->rightChild;

	if (temp->rightChild)
	{
		parent->rightChild = temp->rightChild;
	}
	else
	{
		parent->rightChild = temp->leftChild;
	}
	delete temp;
	return true;
}

SearchTree& SearchTree::operator=(const SearchTree& other)
{
	if (this == &other)
	{
		return *this;
	}
	BinaryTree::operator=(other);
	return *this;
}