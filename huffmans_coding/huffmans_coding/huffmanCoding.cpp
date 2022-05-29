#include "huffmanCoding.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

void HuffmanCoding::build(const char* fileName, const char* treeFileName)
{
	char character;
	const int charactersAmount = 256;
	int* allCharacters = new int[charactersAmount];
	for (int i = 0; i < charactersAmount; i++)
	{
		allCharacters[i] = 0;
	}

	ifstream file(fileName);

	if (!file.is_open())
	{
		cerr << "\nunable to open file";
		return;
	}

	while (!file.eof())
	{
		character = file.get();
		if (!file.eof())
		{
			allCharacters[(unsigned char)character]++;
		}
	}

	file.close();

	std::list<HuffmanNode*> nodes;
	for (int i = 0; i < charactersAmount; i++)
	{
		if (allCharacters[i])
		{
			HuffmanNode* temp = new HuffmanNode(allCharacters[i]);
			temp->symbols.set_bit(1, i);
			nodes.push_back(temp);
		}
	}

	nodes.sort(compare);
	std::list<HuffmanNode*>::iterator nodesIterator;

	while (nodes.size() > 1)
	{

		HuffmanNode* first = nodes.front();
		nodes.pop_front();
		HuffmanNode* second = nodes.front();
		nodes.pop_front();

		HuffmanNode* newNode = new HuffmanNode(first->frequency + second->frequency);
		newNode->leftChild = first;
		newNode->rightChild = second;
		newNode->symbols |= first->symbols;
		newNode->symbols |= second->symbols;

		if (!nodes.size())
		{
			nodes.push_back(newNode);
		}
		else if (newNode->frequency <= nodes.front()->frequency)
		{
			nodes.push_front(newNode);
		}
		else if (newNode->frequency >= nodes.back()->frequency)
		{
			nodes.push_back(newNode);
		}
		else {

			nodesIterator = nodes.begin();

			for (HuffmanNode* temp : nodes)
			{
				if (temp->frequency > newNode->frequency)
				{
					nodes.insert(nodesIterator, newNode);
					break;
				}
				advance(nodesIterator, 1);
			}
		}
	}
	exportTree(nodes.front());
}


int HuffmanCoding::encode(const char* originalText, const char* codedText, const char* treeFileName)
{
	importTree(treeFileName);
	int oldSize = m_root->frequency * 8;

	map<char, BooleanVector> codes;
	codeSymbols(m_root, codes);

	ifstream original(originalText);
	ofstream result(codedText);
	if (!original.is_open() || original.eof())
	{
		return -1;
	}

	if (!result.is_open())
	{
		build(originalText, treeFileName);
	}

	char symbol;
	BooleanVector resultBV;

	while (!original.eof())
	{
		symbol = original.get();
		resultBV <<= codes[symbol].get_size();
		//cout << resultBV << " | " << codes[symbol] << endl;
		resultBV |= codes[symbol];
		//cout << resultBV << endl;
		//cout << codes[symbol] << " " << symbol << " ";
		//cout << symbol;
	}

	//cout << endl << resultBV << endl;

	cout << resultBV.get_size() << endl;
	cout << oldSize << endl;

	resultBV.filePrint(codedText);

	original.close();
	result.close();

	return ((double)resultBV.get_size() / oldSize * 100);
}

void HuffmanCoding::codeSymbols(HuffmanNode* node, map<char, BooleanVector>& codes) const
{
	codeSymbols(m_root->leftChild, BooleanVector(1, 0), codes);
	codeSymbols(m_root->rightChild, BooleanVector(1, 1), codes);
}

void HuffmanCoding::codeSymbols(HuffmanNode* node,
	BooleanVector code,
	map<char, BooleanVector>& codes) const
{
	if (!node)
	{
		return;
	}


	if (!node->leftChild && !node->rightChild)
	{
		char symbol;
		for (int i = 0; i < 256; i++)
		{
			if (node->symbols[i])
			{
				symbol = (char)i;
				break;
			}
		}
		codes[symbol] = code;
		//cout << symbol << ": " << codes[symbol] << endl;
	}

	//code.resize(code.m_size + 1);

	if (node->leftChild)
	{
		codeSymbols(node->leftChild, code << 1, codes);
	}

	if (node->rightChild)
	{
		codeSymbols(node->rightChild, (code << 1) | BooleanVector(1, 1), codes);
	}
}

bool HuffmanCoding::decode(const char* codedText,
	const char* decodedText,
	const char* treeFileName)
{
	ofstream decoded(decodedText);

	if (!decoded.is_open())
	{
		return false;
	}
	
	BooleanVector bv;
	bv.getFromFile(codedText);

	//cout << endl << bv << endl;

	importTree(treeFileName);
	if (!m_root)
	{
		return false;
	}

	HuffmanNode* temp = m_root;

	for (int i = bv.get_size() - 1; i >= 0; i--)
	{
		if (bv[i])
		{
			if (temp->rightChild)
			{
				temp = temp->rightChild;
			}
			else
			{
				decoded << temp->symbols;
				temp = m_root->rightChild;
			}
		}
		else
		{
			if (temp->leftChild)
			{
				temp = temp->leftChild;
			}
			else
			{
				decoded << temp->symbols;
				temp = m_root->leftChild;
			}
		}
	}

	decoded.close();

	return true;
}

void HuffmanCoding::importTree(const char* treeFileName)
{
	if (!treeFileName)
	{
		return;
	}

	ifstream treeFile(treeFileName);
	if (!treeFile.is_open() || treeFile.eof())
	{
		return;
	}

	int amountOfSymbols, frequency;

	m_root = new HuffmanNode();
	treeFile >> amountOfSymbols;
	treeFile.get();
	
	if (amountOfSymbols > 0)
	{
		for (int i = 0; i < amountOfSymbols; i++)
		{
			m_root->symbols.set_bit(1, treeFile.get());
		}

		treeFile.get();
		treeFile >> frequency;
		m_root->frequency = frequency;
	}

	std::vector<HuffmanNode*> currentLevelNodes;
	currentLevelNodes.push_back(m_root);

	while (currentLevelNodes.size())
	{
		std::vector<HuffmanNode*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (HuffmanNode* node : currentLevelNodes)
		{
			treeFile >> amountOfSymbols;
			treeFile.get();
			if (amountOfSymbols > 0)
			{
				node->leftChild = new HuffmanNode();
				for (int i = 0; i < amountOfSymbols; i++)
				{
					node->leftChild->symbols.set_bit(1, treeFile.get());
				}

				treeFile.get();
				treeFile >> frequency;
				node->leftChild->frequency = frequency;

				nextLevelNodes.push_back(node->leftChild);
			}
			else
			{
				node->leftChild = nullptr;
			}

			treeFile >> amountOfSymbols;
			treeFile.get();
			if (amountOfSymbols > 0)
			{
				node->rightChild = new HuffmanNode();
				for (int i = 0; i < amountOfSymbols; i++)
				{
					node->rightChild->symbols.set_bit(1, treeFile.get());
				}

				treeFile.get();
				treeFile >> frequency;
				node->rightChild->frequency = frequency;

				nextLevelNodes.push_back(node->rightChild);
			}
			else
			{
				node->rightChild = nullptr;
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
}

bool HuffmanCoding::exportTree(HuffmanNode* root, const char* treeFileName)
{
	ofstream treeFile(treeFileName);
	if (!treeFile.is_open())
	{
		return false;
	}

	treeFile << root->symbols.weight() << " ";
	treeFile << root->symbols << " ";
	treeFile << root->frequency << " " << endl;

	std::vector<HuffmanNode*> currentLevelNodes;
	currentLevelNodes.push_back(root);

	while (currentLevelNodes.size())
	{
		std::vector<HuffmanNode*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (HuffmanNode* node : currentLevelNodes)
		{
			if (node->leftChild)
			{
				treeFile << node->leftChild->symbols.weight() << " ";
				treeFile << node->leftChild->symbols << " ";
				treeFile << node->leftChild->frequency << " ";
				nextLevelNodes.push_back(node->leftChild);
			}

			if (!node->leftChild)
			{
				treeFile << " 0 ";
			}

			if (node->rightChild)
			{
				treeFile << node->rightChild->symbols.weight() << " ";
				treeFile << node->rightChild->symbols << " ";
				treeFile << node->rightChild->frequency << " ";
				nextLevelNodes.push_back(node->rightChild);
			}

			if (!node->rightChild)
			{
				treeFile << " 0 ";
			}
		}
		treeFile << endl;
		currentLevelNodes.swap(nextLevelNodes);
	}
	treeFile.close();
	return true;
}

HuffmanCoding::HuffmanCoding(const HuffmanCoding& copy)
{
	copyTree(copy.m_root);
}

void HuffmanCoding::copyTree(const HuffmanNode* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}

	if (subTreeRoot == m_root)
	{
		return;
	}
	if (m_root)
	{
		deleteTree(m_root);
	}

	m_root = new HuffmanNode(subTreeRoot->frequency, subTreeRoot->symbols);

	if (subTreeRoot->numberOfChildren() > 0)
	{
		copyNodes(subTreeRoot, m_root);
	}
}

void HuffmanCoding::copyNodes(const HuffmanNode* subTreeRoot, HuffmanNode* copyRoot)
{
	if (subTreeRoot == nullptr || copyRoot == nullptr)
	{
		return;
	}

	if (subTreeRoot->leftChild)
	{
		addLeft(copyRoot, subTreeRoot->leftChild->frequency, subTreeRoot->leftChild->symbols);
		copyNodes(subTreeRoot->leftChild, copyRoot->leftChild);
	}

	if (subTreeRoot->rightChild)
	{
		addRight(copyRoot, subTreeRoot->rightChild->frequency, subTreeRoot->rightChild->symbols);
		copyNodes(subTreeRoot->rightChild, copyRoot->rightChild);
	}
}

void HuffmanCoding::addLeft(HuffmanNode* subTreeRoot, const int frequency, Set symbols)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}
	if (!subTreeRoot->leftChild)
	{
		subTreeRoot->leftChild = new HuffmanNode(frequency, symbols);
	}
}

void HuffmanCoding::addRight(HuffmanNode* subTreeRoot, const int frequency, Set symbols)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}
	if (!subTreeRoot->rightChild)
	{
		subTreeRoot->rightChild = new HuffmanNode(frequency, symbols);
	}
}

HuffmanCoding::~HuffmanCoding()
{
	if (m_root)
	{
		deleteTree(m_root);
	}
}

void HuffmanCoding::deleteTree(HuffmanNode* subTreeRoot)
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

	if (subTreeRoot == m_root)
	{
		m_root = nullptr;
	}
	delete subTreeRoot;
}

int HuffmanNode::numberOfChildren() const
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