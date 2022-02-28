#include <iostream>
#include <fstream>
#include <string>
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

bool isFileSorted(const char *name, int n)
{
	fstream file(name, ios::in);

	if (!file.is_open())
	{
		cerr << "\ncan't open file";
		return false;
	}

	int number1, number2, count = 2;
	file >> number1;
	file >> number2;

	while (!file.eof())
	{
		count++;
		if (number1 > number2)
		{
			return false;
		}
		number1 = number2;
		file >> number2;
	}
	file.close();
	if (count != n)
	{
		return false;
	}
	return true;
}

int select(int j, int *fibonacci, int *fictitiousSegments, int &lvl, int n)
{
	int temp;
	if (fictitiousSegments[j] < fictitiousSegments[j + 1])
	{
		j++;
	}
	else
	{
		if (fictitiousSegments[j] == 0)
		{
			lvl++;
			temp = fibonacci[0];
			for (int i = 0; i < n - 1; i++)
			{
				fictitiousSegments[i] = temp + fibonacci[i + 1] - fibonacci[i];
				fibonacci[i] = temp + fibonacci[i + 1];
			}
		}
		j = 0;
	}
	fictitiousSegments[j]--;
	return j;
}

bool merging(string *fileName, int *fictitiousSegments, int lvl, int n);

bool partitioning(const char *mainFileName, string *fileName, int n)
{
	int *fibonacci = new int[n];
	int *fictitiousSegments = new int[n];
	fstream **file = new fstream*[n];
	for (int i = 0; i < n - 1; i++)
	{
		file[i] = new fstream(fileName[i], ios::out);
		if (!file[i]->is_open())
		{
			cerr << "\ncan't create file 'f" << i << ".txt'";
			delete[]fibonacci;
			delete[]fictitiousSegments;
			for (int j = 0; j < i; j++)
			{
				delete file[j];
			}
			delete[]file;
			return false;
		}
		fibonacci[i] = 1;
		fictitiousSegments[i] = 1;
	}
	fibonacci[n - 1] = fictitiousSegments[n - 1] = 0;
	int lvl = 1, j = 0;
	ifstream mainFile(mainFileName);
	if (!mainFile.is_open())
	{
		cerr << "\ncan't open main file";
		delete[]fibonacci;
		delete[]fictitiousSegments;
		for (int i = 0; i < n - 1; i++)
		{
			delete file[i];
		}
		delete[]file;
		return false;
	}
	int num1, num2;
	mainFile >> num1;
	while (!mainFile.eof())
	{
		j = select(j, fibonacci, fictitiousSegments, lvl, n);
		while (!mainFile.eof())
		{
			*file[j] << " " << num1;
			mainFile >> num2;
			if (num2 < num1)
			{
				num1 = num2;
				break;
			}
			num1 = num2;
		}
		*file[j] << " " << -1;
	}
	for (int i = 0; i < n - 1; i++)
	{
		file[i]->close();
	}
	mainFile.close();
	if (!merging(fileName, fictitiousSegments, lvl, n))
	{
		return false;
	}
	delete[]fibonacci;
	delete[]fictitiousSegments;
	for (int i = 0; i < n - 1; i++)
	{
		delete file[i];
	}
	delete[]file;
	return true;
}

bool isArrayNegative(int *array, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (array[i] >= 0)
		{
			return false;
		}
	}
	return true;
}

int findMin(int *array, int n)
{
	int min = array[0], minIndex = 0;
	for (int i = 0; i < n; i++)
	{
		if ((min < 0 || array[i] < min) && array[i] >= 0)
		{
			min = array[i];
			minIndex = i;
		}
	}
	return minIndex;
}

void writeResult(string name, const char *resultName)
{
	fstream file(name, ios::in);
	if (!file.is_open())
	{
		cerr << "\ncan't open file " << name;
		return;
	}
	fstream result(resultName, ios::out);
	if (!result.is_open())
	{
		cerr << "\ncan't create file" << resultName;
		return;
	}
	int num;
	while (!file.eof())
	{
		file >> num;
		if (num >= 0)
		{
			result << " " << num;
		}
	}
	file.close();
	result.close();
}

bool merging(string *fileName, int *fictitiousSegments, int lvl, int n)
{
	fstream **file = new fstream*[n];
	int *minInSegments = new int[n];
	for (int i = 0; i < n - 1; i++)
	{
		file[i] = new fstream(fileName[i], ios::in);
		if (!file[i]->is_open())
		{
			cerr << "\ncan't open file 'f" << i << ".txt'";
			for (int j = 0; j < i; j++)
			{
				delete file[j];
			}
			delete[]file;
			delete[]minInSegments;
			return false;
		}
	}
	file[n - 1] = new fstream(fileName[n - 1], ios::out);
	if (!file[n - 1]->is_open())
	{
		cerr << "\ncan't create file 'f" << n - 1 << ".txt'";
		for (int i = 0; i < n; i++)
		{
			delete file[i];
		}
		delete[]file;
		delete[]minInSegments;
		return false;
	}
	while (lvl > 0)
	{
		while (!file[n - 2]->eof())
		{
			bool allFilesHaveFictitiousSegments = true;
			for (int i = 0; i < n - 1 && allFilesHaveFictitiousSegments; i++)
			{
				if (fictitiousSegments[i] == 0)
				{
					allFilesHaveFictitiousSegments = false;
				}
			}
			if (allFilesHaveFictitiousSegments)
			{
				for (int i = 0; i < n - 1; i++)
				{
					fictitiousSegments[i]--;
				}
				fictitiousSegments[n - 1]++;
			}
			else
			{
				for (int i = 0; i < n; i++)
				{
					minInSegments[i] = -1;
				}

				for (int i = 0; i < n - 1; i++)
				{
					if (fictitiousSegments[i] == 0)
					{
						*file[i] >> minInSegments[i];
					}
					else
					{
						fictitiousSegments[i]--;
					}
				}
				while (!isArrayNegative(minInSegments, n))
				{
					int j = findMin(minInSegments, n);
					*file[n - 1] << " " << minInSegments[j];
					*file[j] >> minInSegments[j];
				}
				*file[n - 1] << " " << -1;
			}
		}
		lvl--;
		file[n - 1]->close();
		file[n - 2]->close();
		file[n - 1] = new fstream(fileName[n - 1], ios::in);
		if (!file[n - 1]->is_open())
		{
			cerr << "\ncan't open file " << fileName[n - 1];
			for (int i = 0; i < n; i++)
			{
				delete file[i];
			}
			delete[]file;
			delete[]minInSegments;
			return false;
		}
		file[n - 2] = new fstream(fileName[n - 2], ios::out);
		if (!file[n - 2]->is_open())
		{
			cerr << "\ncan't create file " << fileName[n - 2];
			for (int i = 0; i < n; i++)
			{
				delete file[i];
			}
			delete[]file;
			delete[]minInSegments;
			return false;
		}

		fstream *tempFile = file[n - 1]; //двигаем указатели
		int tempD = fictitiousSegments[n - 1];
		string tempName = fileName[n - 1];
		for (int i = n - 1; i > 0; i--)
		{
			file[i] = file[i - 1];
			fictitiousSegments[i] = fictitiousSegments[i - 1];
			fileName[i] = fileName[i - 1];
		}
		file[0] = tempFile;
		fictitiousSegments[0] = tempD;
		fileName[0] = tempName;
	}
	for (int i = 0; i < n; i++)
	{
		file[i]->close();
	}
	writeResult(fileName[0], "result.txt");
	delete[]minInSegments;
	for (int i = 0; i < n; i++)
	{
		delete file[i];
	}
	delete[]file;
	return true;
}

bool multiphaseSorting(const char *mainFileName, int n = 3)
{
	string *fileName = new string[n];
	for (int i = 0; i < n; i++)
	{
		fileName[i] = "f" + to_string(i) + ".txt";
	}
	if (!partitioning(mainFileName, fileName, n))
	{
		return false;
	}
	delete[]fileName;
	return true;
}

int createAndSortFile(const char *fileName, const int numbersCount, const int maxNumberValue)
{
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	multiphaseSorting(fileName);

	if (!isFileSorted("result.txt", numbersCount)) {
		return -2;
	}

	return 1;
}

int main()
{
	const int numbersCount = 1000000;
	const int maxNumberValue = 100000;
	for (int i = 0; i < 10; i++)
	{
		switch (createAndSortFile("test.txt", numbersCount, maxNumberValue))
		{
		case 1:
			std::cout << "Test passed." << std::endl;
			break;

		case -1:
			std::cout << "Test failed: can't create file." << std::endl;
			break;

		case -2:
			std::cout << "Test failed: file isn't sorted." << std::endl;
			break;
		}
	}
}

