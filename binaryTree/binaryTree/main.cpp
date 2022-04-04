#include "binaryTree.h"
#include <iostream>
#include <time.h>

int main()
{
	using std::cout;
	using std::endl;
	srand(time(0));

	BinaryTree bt;
	int treeSize = 15;
	for (int i = 0; i < treeSize; i++)
		bt.addNode(i);

	bt.print();

	cout << endl;
	cout << "index by key 6: " << bt.getIndexByKey(6) << endl;
	cout << "key by index 3: " << bt.getKeyByIndex(3) << endl;
	cout << "delete node(index 21): " << (bt.deleteNode(21) ? "true" : "false") << endl;
	cout << "delete node(index 5): " << (bt.deleteNode(5) ? "true" : "false") << endl;
	bt.print();
	BinaryTree bt1(bt);
	bt1.print();
	cout << "\nbt1 delete subtrees: ";
	bt1.deleteSubTrees(2);
	bt1.print();
	cout << "is bt1 empty? " << (bt1.isEmpty() ? "true" : "false") << endl;
	bt1.deleteTree();
	cout << "is bt1 empty(after deleting)? " << (bt1.isEmpty() ? "true" : "false") << endl;
	bt1 = bt.copySubTree(1);
	bt1.print();
	cout << "bt1 height: " << bt1.treeHeight() << endl;
	cout << "bt1 amount of nodes: " << bt1.numberOfNodes() << endl;
	cout << "bt1 max key: " << bt1.maxKey() << endl;
	cout << "bt1 min key: " << bt1.minKey() << endl;
	cout << "bt1 add node, key = 21: " << (bt1.addNode(21) ? "true" : "false");
	bt1.print();
	cout << "bt1 delete node, key = 21: " << (bt1.deleteNodeKey(21) ? "true" : "false") << endl;
	cout << "bt1 delete node, key = 26: " << (bt1.deleteNodeKey(26) ? "true" : "false") << endl;
	bt1.print();
	cout << "is bt1 balanced? " << (bt1.isTreeBalanced() ? "true" : "false") << endl;
	cout << "bt1 keys sum: " << bt1.keysSum() << endl;
	cout << "bt1 key 5 level: " << bt1.findKeyLevel(5) << endl;
	cout << "bt1 key 21 level: " << bt1.findKeyLevel(21) << endl;
	std::vector<int> keys = bt1.treeKeysVector();
	for (int x : keys)
	{
		cout << x << " ";
	}
	cout << endl;
	cout << "bt1 print leaves: " << endl;
	bt1.printLeaves();
	bt = bt1;
	bt.print();
	bt = bt;

	return 0;
}