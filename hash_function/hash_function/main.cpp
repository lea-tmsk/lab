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

	ht.deleteKey(21, "heh");
	ht.deleteKey(10, " ");

	HashTable<std::string> ht1(10);

	ht1.changeHashFunction(&hf2);

	ht1.addKey(10, "aha");
	ht1.addKey(21, "heh");
	ht1.addKey(666, "hello");
	ht1.addKey(11, "i can't");

	ht1.print();

	return 0;
}