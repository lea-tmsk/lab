#include "searchTree.h"

int SearchTree::getMin(const int nodeIndex) const
{
	return getMin(node(nodeIndex));
}

int SearchTree::getMin(Node* subTreeRoot) const
{
	Node* temp = subTreeRoot;
	while (temp->leftChild)
	{
		temp = temp->leftChild;
	}
	return temp->getKey();
}

int SearchTree::getMax(const int nodeIndex) const
{
	return getMax(node(nodeIndex));
}

int SearchTree::getMax(Node* subTreeRoot) const
{
	Node* temp = subTreeRoot;
	while (temp->rightChild)
	{
		temp = temp->rightChild;
	}
	return temp->getKey();
}

bool SearchTree::addNode(const int key, const int nodeIndex)
{
	return addNode(node(nodeIndex), key);
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

bool SearchTree::deleteNodeByKey(const int key, const int nodeIndex)
{
	return deleteNodeByIndex(node(nodeIndex), getIndexByKey(key, nodeIndex));
}

bool SearchTree::deleteNodeByKey(Node* subTreeRoot, const int key)
{
	return deleteNodeByIndex(subTreeRoot, getIndexByKey(subTreeRoot, key));
}

bool SearchTree::deleteNodeByIndex(const int deleteIndex, const int nodeIndex)
{
	return deleteNodeByIndex(node(nodeIndex), deleteIndex);
}

bool SearchTree::deleteNodeByIndex(Node* subTreeRoot, const int deleteIndex)
{
	if (subTreeRoot == nullptr)
	{
		return false;
	}

	Node* temp = node(subTreeRoot, deleteIndex);

	if (temp == nullptr)
	{
		return false;
	}

	if (temp == m_root)
	{
		return deleteRoot();
	}

	Node* parent = findParent(temp);

	if (!temp->numberOfChildren())
	{
		if (parent->leftChild == temp)
		{
			parent->leftChild = nullptr;
		}
		else
		{
			parent->rightChild = nullptr;
		}
		delete temp;
		return true;
	}

	if (temp->numberOfChildren() == 2)
	{
		if (parent->leftChild == temp)
		{
			return deleteLeftBothChildren(parent, subTreeRoot);
		}
		else
		{
			return deleteRightBothChildren(parent, subTreeRoot);
		}
	}

	if (parent->leftChild == temp)
	{
		return deleteLeftOneChild(parent, subTreeRoot);
	}

	if (parent->rightChild == temp)
	{
		return deleteRightOneChild(parent, subTreeRoot);
	}
	return false;
}

int SearchTree::getIndexByKey(const int key, const int nodeIndex) const
{
	return BinaryTree::getIndexByKey(key, nodeIndex);
}

int SearchTree::getIndexByKey(Node* subTreeRoot, const int key) const
{
	return BinaryTree::getIndexByKey(subTreeRoot, key);
}

int SearchTree::getLevelByKey(const int key, const int nodeIndex) const
{
	return getLevelByKey(node(nodeIndex), key);
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

bool SearchTree::deleteLeftBothChildren(Node* parent, Node* subTreeRoot)
{
	Node* temp = parent->leftChild;
	parent->leftChild = temp->rightChild;
	Node* place = subTreeRoot;

	while (place->leftChild)
	{
		place = place->leftChild;
	}

	place->leftChild = temp->leftChild;
	delete temp;
	return true;
}

bool SearchTree::deleteRightBothChildren(Node* parent, Node* subTreeRoot)
{
	Node* temp = parent->rightChild;
	parent->rightChild = temp->leftChild;
	Node* place = subTreeRoot;

	while (place->rightChild)
	{
		place = place->rightChild;
	}

	place->rightChild = temp->rightChild;
	delete temp;
	return true;
}

bool SearchTree::deleteLeftOneChild(Node* parent, Node* subTreeRoot)
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

bool SearchTree::deleteRightOneChild(Node* parent, Node* subTreeRoot)
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