#include "binaryTree.h"
#include "searchTree.h"
#include "balancedTree.h"
#include <iostream>
#include <time.h>


int main()
{
	using std::cout;
	using std::endl;
	srand(time(0));

	BalancedTree bt;
	int treeSize = 200, x;
	std::vector<int> keys;
	for (int i = 0; i < treeSize; i++)
	{
		//bt.addNode((i % 2) ? 100-i : i);
		x = rand() % 200;
		bt.addNode(x);
		keys.push_back(x);
		//bt.print();
		//cout << endl;
		//cout << "nodes:" << bt.numberOfNodes() << endl;
		if (bt.isTreeBalanced() && bt.isSearchTree())
		{
			//cout << "is balanced and search tree" << endl;
		}
		else
		{
			if (!bt.isTreeBalanced())
				cout << "ERROR: isn't balanced" << endl;
			else
				cout << "error: isn't search tree" << endl;
			break;
		}
		//cout << (bt.isTreeBalanced() ? "is balanced" : "isn't balanced") << endl;
		//cout << endl;
	}
	bt.print();
	cout << "nodes:" << bt.numberOfNodes() << endl;
	cout << (bt.isTreeBalanced() ? "is balanced" : "isn't balanced") << endl;

	for (int i = 0; i < treeSize; i++)
	{
		//cout << "delete key: " << keys[i] << endl;
		//bt.print();
		bt.deleteNodeByKey(keys[i]);
		if (bt.isTreeBalanced() && (bt.isEmpty() || bt.isSearchTree()))
		{
			cout << "is balanced and search tree" << endl;
		}
		else
		{
			bt.print();
			cout << "\nERROR: isn't balanced" << endl;
			break;
		}
	}
	cout << (bt.isEmpty() ? "tree is empty" : "tree isn't empty") << endl;

	return 0;
}