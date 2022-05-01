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
	int treeSize = 1000, x;
	for (int j = 0; j < 10; j++)
	{
		std::vector<int> keys;
		for (int i = 0; i < treeSize; i++)
		{
			x = rand() % 10000;
			//cout << "\nadd node: " << x;
			//bt.print();
			bt.addNode(x);
			keys.push_back(x);
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
		}
		cout << "\nnodes:" << bt.numberOfNodes() << endl;
		//bt.print();
		cout << (bt.isTreeBalanced() ? "is balanced" : "isn't balanced") << endl;
		cout << (bt.isSearchTree() ? "is a search tree" : "isn't a search tree") << endl;
		int deleted = 0;
		for (int i = 0; i < treeSize; i++)
		//for (int i = treeSize; i >= 0; i--)
		{
			//cout << "\ndelete index: " << i;
			//bt.print();
			if (bt.deleteNodeByKey(keys[i]))
			//if (bt.deleteNodeByIndex(0))
			{
				deleted++;
			}
			//cout << "\nnodes amount: " << bt.numberOfNodes();
			if (bt.isTreeBalanced() && (bt.isEmpty() || bt.isSearchTree()))
			{
				//cout << "is balanced and search tree" << endl;
			}
			else
			{
				bt.print();
				cout << "\nERROR: isn't balanced" << endl;
				break;
			}
		}
		cout << "\ndeleted: " << deleted;
		cout << (bt.isEmpty() ? "\ntree is empty" : "\ntree isn't empty") << endl;
		bt.deleteTree();
		cout << endl;
	}

	BinaryTree* ptr = &bt;
	ptr->addNode(10);
	ptr->addNode(10);
	ptr->addNode(14);
	ptr->addNode(15);
	bt.print();

	return 0;
}