#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <time.h>

int main()
{
	srand(time(0));
	BinaryTree bt;
	bt.isEmpty();
	//bt.addNode(5);
	int treeSize = 20;
	for (int i = 0; i < treeSize; i++)
		//bt.addNode(rand() % treeSize);
		bt.addNode(i);
	/*for (int i = 0; i < bt.treeHeight(); i++)
	{
		bt.print(i);
		std::cout << std::endl;
	}*/
	std::cout << "key = 0, index = " << bt.getIndexByKey(0);
	std::cout << std::endl;

	bt.print();
	std::cout << std::endl;
	std::cout << bt.numberOfNodes() << std::endl;
	BinaryTree bt2(bt);
	bt2.print();
	std::cout << std::endl;
	std::cout << (bt.isTreeBalanced() ? "balanced\n" : "isn't balanced\n");
	BinaryTree bt1;
	//bt1 = bt;
//	bt1.print();
	//for (int i = 0; i < 10000; i++)
	//{
	//	bt1 = bt;
	//}
	//for (int i = 0; i < bt1.treeHeight(); i++)
	//{
	//	bt1.print(i);
	//	std::cout << std::endl;
	//}

	bt1.addNode(5);
	bt1.addLeft(4, 0);
	bt1.addLeft(3, 1);
	bt1.addLeft(2, 2);

	bt1.print();
	std::cout << std::endl;
	//bt1.newprint();
	std::cout << std::endl;

	std::cout << (bt1.isTreeBalanced() ? "balanced" : "isn't balanced");

	bt.deleteSubTrees(2);
	std::cout << std::endl;
	bt.print();
	std::cout << std::endl;
	std::cout << bt.numberOfNodes();
	
	std::vector<int> keys;
	keys = bt.treeKeysVector(5);

	std::cout << std::endl;
	for (int x : keys)
	{
		std::cout << x << " ";
	}

	std::cout << std::endl;
	std::cout << bt.treeHeight();
	std::cout << std::endl;
	std::cout << bt.minKey();
	std::cout << std::endl;
	std::cout << bt.maxKey();
	std::cout << std::endl;
	std::cout << bt.keysSum();
	std::cout << std::endl;
	bt.printLeaves();
	bt.deleteTree();
	return 0;
}