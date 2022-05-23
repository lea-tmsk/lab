#include "set.h"
#include <vector>
#include <list>
#include <map>
#pragma once

class HuffmanNode
{
public:
	HuffmanNode(int frequency = 0,
				Set symbols = Set(),
				HuffmanNode* leftChild = nullptr,
				HuffmanNode* rightChild = nullptr) :
				frequency(frequency),
				symbols(symbols),
				leftChild(leftChild),
				rightChild(rightChild)
	{}

	~HuffmanNode() = default;

	int numberOfChildren() const;

	Set symbols;
	int frequency = 0;
	HuffmanNode* leftChild = nullptr;
	HuffmanNode* rightChild = nullptr;
};

struct 
{
	bool operator()(HuffmanNode* first, HuffmanNode* second) const
	{
		return first->frequency < second->frequency;
	}
} compare;

class HuffmanCoding
{
public:
	HuffmanCoding() = default;
	HuffmanCoding(const HuffmanCoding& copy);
	~HuffmanCoding();

	void build(const char* fileName, const char* treeFileName);

	double encode(const char* originalText,
		  	   const char* codedText,
			   const char* treeFileName = "tree.txt");

	bool decode(const char* codedText,
				const char* decodedText,
				const char* treeFileName);
	

	void codeSymbols(HuffmanNode* node, map<char, BooleanVector>& codes) const;
	void codeSymbols(HuffmanNode* node,
		BooleanVector code,
		map<char, BooleanVector>& codes) const;
	void importTree(const char* treeFileName);
	bool exportTree(HuffmanNode* root, const char* treeFileName = "tree.txt");


	void copyTree(const HuffmanNode* subTreeRoot);
	void copyNodes(const HuffmanNode* subTreeRoot, HuffmanNode* copyRoot);
	void addLeft(HuffmanNode* subTreeRoot, const int frequency, Set symbols);
	void addRight(HuffmanNode* subTreeRoot, const int frequency, Set symbols);
	void deleteTree(HuffmanNode* subTreeRoot);

private:
	HuffmanNode* m_root;
};

