#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
using namespace std;

bool createFileWithRandomNumbers(const char *name, const int numbersCount, const int maxNumberValue)
{
	ofstream file(name);

	if (!file.is_open())
	{
		cerr << "\ncan't create file";
		return false;
	}

	int number;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, maxNumberValue);
	generator.seed(time(0));
	for (int i = 0; i < numbersCount; i++)
	{
		number = distribution(generator);
		file << number;
		file << " ";
	}
	file.close();
	return true;
}

bool isFileSorted(const char *name)
{
	ifstream file(name);

	if (!file.is_open())
	{
		cerr << "\ncan't open file";
		return false;
	}

	int number1, number2;
	file >> number1;
	file >> number2;

	while (!file.eof())
	{
		if (number1 > number2)
		{
			return false;
		}
		number1 = number2;
		file >> number2;
	}
	file.close();
	return true;
}

int main()
{
	createFileWithRandomNumbers("test.txt", 100, 1000);
	cout << (isFileSorted("test.txt") ? "true" : "false");
}