#include "huffmanCoding.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HuffmanCoding hc;
	hc.build("text.txt", "tree.txt");
	cout << hc.encode("text.txt", "coded.txt", "tree.txt") << endl;
	hc.decode("coded.txt", "decoded.txt", "tree.txt");

	return 0;
}