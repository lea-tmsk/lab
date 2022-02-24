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

int select(int *d, int *a, int &lvl, int j, int n)
{
	if (d[j] < d[j + 1])
	{
		j++;
	}
	else
	{
		if (d[j] == 0)
		{
			lvl++;
			int temp = a[0];
			j = 0;
			for (int i = 0; i < n - 1; i++)
			{
				d[i] = a[i + 1] - a[i] + temp;
				a[i] = a[i + 1] + temp;
			}
		}
		j = 0;
	}
	d[j]--;
	return j;
}

bool merge(const char *name, string *name_f, int lvl, int *d, int n);

bool partitioning(const char *name, string *name_f, int *d, int *a, int n)
{
	fstream **file = new fstream*[n];
	for (int i = 0; i < n - 1; i++)
	{
		file[i] = new fstream(name_f[i], ios::out);
		if (!file[i]->is_open())
		{
			cerr << "\ncan't create file[" << i << "]";
			return false;
		}
	}
	ifstream mainFile(name);
	if (!mainFile.is_open())
	{
		cerr << "\ncan't open file: " << name;
		return false;
	}
	int lvl = 1, j = 0;
	a[n - 1] = 0; 
	d[n - 1] = 0;
	for (int i = 0; i < n - 1; i++)
	{
		a[i] = 1;
		d[i] = 1;
	}

	int num1, num2 = 0;
	mainFile >> num1;
	while (!mainFile.eof())
	{
		j = select(d, a, lvl, j, n);
		while (!mainFile.eof())
		{
			if (num1 < 0)
			{
				num1 = num2;
			}
			mainFile >> num2;
			*file[j] << " " << num1;
			if (num2 < num1)
			{
				num1 = -1;
				*file[j] << " " << -1;
				break;
			}
			num1 = num2;
		}
		if (mainFile.eof())
		{
			*file[j] << " " << -1;
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		file[i]->close();
	}
	if (!merge(name, name_f, lvl, d, n))
	{
		return false;
	}
	return true;
}

int findMin(int *arr, int n)
{
	int min = arr[0], minIndex = 0;
	for (int i = 1; i < n; i++)
	{
		if ((arr[i] < min  || min < 0 ) && arr[i] >= 0)
		{
			min = arr[i];
			minIndex = i;
		}
	}
	return minIndex;
}

bool isArrayNegative(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] >= 0)
		{
			return false;
		}
	}
	return true;
}

bool writeResult(string fileName, const char *resultName)
{
	ofstream result(resultName);
	if (!result.is_open())
	{
		cerr << "\ncan't create file";
		return false;
	}

	ifstream file(fileName);
	if (!file.is_open())
	{
		cerr << "\ncan't open file[0]";
		return false;
	}

	int x;
	while (!file.eof())
	{
		file >> x;
		if (x >= 0)
		{
			result << x << " ";
		}
	}
	file.close();
	result.close();
	return true;
}

bool merge(const char *name, string *name_f, int lvl, int *d, int n)
{
	fstream **file = new fstream*[n];
	int *minInSegments = new int[n];
	
	for (int i = 0; i < n - 1; i++)
	{
		file[i] = new fstream(name_f[i], ios::in);
		if (!file[i]->is_open())
		{
			cerr << "\ncan't open file[" << i << "]";
			return false;
		}
	}
	file[n - 1] = new fstream(name_f[n - 1], ios::out);
	if (!file[n - 1]->is_open())
	{
		cerr << "\ncan't open file: " << name_f[n - 1];
		return false;
	}
	int countRound = 0;
	while (lvl != 0)
	{
		bool allFilesHaveFictitiousSegments = true;
		for (int i = 0; allFilesHaveFictitiousSegments && i < n - 1; i++) //если во всех файлах есть фиктивные отрезки
		{
			if (d[i] == 0)
			{
				allFilesHaveFictitiousSegments = false;
			}
		}
		if (allFilesHaveFictitiousSegments) //"сливаем" по 1 фиктивному отрезку из каждого файла
		{
			for (int i = 0; i < n - 1; i++)
			{
				d[i]--;
			}
		}
		else
		{
			int j;
			for (int i = 0; i < n; i++)
			{
				minInSegments[i] = -1;
			}
			while (!file[n - 2]->eof())
			{
				for (int i = 0; i < n - 1; i++)
				{
					if (d[i] == 0) //сливаем
					{
						*file[i] >> minInSegments[i];
					}
					else
					{
						d[i]--; //уменьшаем кол-во фиктивных отрезков в i-том файле 
					}
				}
				while (!isArrayNegative(minInSegments, n))
				{
					j = findMin(minInSegments, n);
					*file[n - 1] << " " << minInSegments[j];
					*file[j] >> minInSegments[j];
				}
				*file[n - 1] << " " << -1;
			}
		}
		lvl--;
		file[n - 2]->close();
		file[n - 1]->close();
		file[n - 2] = new fstream(name_f[n - 2], ios::out);
		if (!file[n - 2]->is_open())
		{
			cerr << "\ncan't open file: " << name_f[n - 2];
			return false;
		}
		file[n - 1] = new fstream(name_f[n - 1], ios::in);
		if (!file[n - 1]->is_open())
		{
			cerr << "\ncan't open file: " << name_f[n - 1];
			return false;
		}

		fstream *tempFile = file[n - 1]; //двигаем указатели
		int tempD = d[n - 1];
		string tempName = name_f[n - 1];
		for (int i = n - 1; i > 0; i--)
		{
			file[i] = file[i - 1];
			d[i] = d[i - 1];
			name_f[i] = name_f[i - 1];
		}
		file[0] = tempFile;
		d[0] = tempD;
		name_f[0] = tempName;
	}
	for (int i = 0; i < n; i++)
	{
		file[i]->close();
	}

	if (!writeResult(name_f[0], "result.txt"))
	{
		return false;
	}
	return true;
}

bool multiphaseSorting(const char *name, int n = 3) //n - кол-во рабочих файлов
{
	string *name_f = new string[n];
	for (int i = 0; i < n; i++)
	{
		name_f[i] = "f" + to_string(i) + ".txt";
	}
	int *d = new int[n];
	int *a = new int[n];
	if (!partitioning(name, name_f, d, a, n))
	{
		return false;
	}
	return true;
}

int createAndSortFile(const char *fileName, const int numbersCount, const int maxNumberValue)
{
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	multiphaseSorting(fileName);

	if (!isFileSorted("result.txt")) {
		return -2;
	}

	return 1;
}

int main()
{
	const int numbersCount = 10;
	const int maxNumberValue = 2000;
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
