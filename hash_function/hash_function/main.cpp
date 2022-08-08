#include "hash_table.h"
#include <iostream>
#include <string>

int main()
{
	HashTable<std::string> ht(10);

	ht.addKey(10, "aha");
	ht.addKey(21, "heh");
	ht.addKey(666, "hello");
	ht.addKey(11, "i can't");

	ht.print();

	ht.deleteKey(21);
	ht.deleteKey(10);

	HashTable<std::string> ht1(10);

	ht1.addKey(10, "aha");
	ht1.addKey(21, "heh");
	ht1.addKey(666, "hello");
	ht1.addKey(11, "i can't");
	ht1.addKey(22, "ok");
	ht1.addKey(111, "no way");
	ht1.addKey(111, "fgf");

	std::cout << std::endl;
	ht1.print();

	ht1.changeHashFunction(&hf3);

	std::cout << "\nafter changing hash function: \n";
	ht1.print();

	HashTable<std::string> copy;
	copy = ht1;

	ht1.deleteKey(10);
	ht1.deleteKey(21);
	ht1.deleteKey(666);
	ht1.deleteKey(11);
	ht1.deleteKey(22);
	ht1.deleteKey(112);

	std::cout << "\nafter deleting:" << std::endl;
	ht1.print();

	std::cout << "\ncopy: " << std::endl;
	copy.print();

	copy = ht1;

	std::cout << "\nht1 copy: " << std::endl;
	copy.print();

	return 0;
}