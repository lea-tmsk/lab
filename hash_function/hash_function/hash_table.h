#include <math.h>
#include <iostream>
#pragma once

struct IHashFunctions
{
	virtual int hash(int index, int key, int size) = 0;
};

struct HashFunction1 : IHashFunctions
{
	int hash(int index, int key, int size) override
	{
		int hash = key % size;
		for (int i = 0; i < index; i++)
		{
			hash = (hash + i + i * i) % size;
		}
		return hash;
	}
} hf1;

struct HashFunction2 : IHashFunctions
{
	int hash(int index, int key, int size) override
	{
		int hash = key % size;
		double a = -(1 - sqrt(5)) / 2;
		for (int i = 0; i < index; i++)
		{
			hash = (int)(hash * a * size) % size;
		}
		return hash;
	}
} hf2;

struct HashFunction : IHashFunctions
{
	int hash(int index, int key, int size) override
	{
		int hash;
		hash = (key % size + index * (1 + key % abs(size - 2))) % size;
	}
} hf3;

template<typename T>
class HashTable
{
public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable<T>& copy);
	~HashTable();

	void addKey(int key, T value);
	void deleteKey(int key, T value);
	bool checkKey(int key, T value);
	void changeHashFunction(IHashFunctions* newHashFunction);

	HashTable<T>& operator=(const HashTable<T>& ht);

	void print();

private:
	IHashFunctions* hf;
	int m_size;
	int* m_keys;
	T* m_values;
	bool* m_empty;
};


template<typename T>
HashTable<T>::HashTable()
{
	m_size = 1;
	m_keys = new int[m_size];
	m_values = new T[m_size];
	m_empty = new bool[m_size];

	m_keys[0] = 0;
	m_values[0] = T();
	m_empty[0] = true;
	hf = &hf1;
}

template<typename T>
HashTable<T>::HashTable(int size)
{
	m_size = size;
	m_keys = new int[m_size];
	m_values = new T[m_size];
	m_empty = new bool[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = 0;
		m_values[i] = T();
		m_empty[i] = true;
	}
	hf = &hf1;
}

template<typename T>
HashTable<T>::HashTable(const HashTable<T>& copy)
{
	if (&copy == this)
	{
		return;
	}

	if (m_size != copy.m_size)
	{
		m_size = copy.m_size;
		if (m_keys)
		{
			delete[]m_keys;
		}
		m_keys = new int[m_size];
		if (m_values)
		{
			delete[]m_values;
		}
		m_values = new T[m_size];
		if (m_empty)
		{
			delete[]m_empty;
		}
		m_empty = new bool[m_size];
	}

	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = copy.m_keys[i];
		m_values[i] = copy.m_values[i];
		m_empty[i] = copy.m_empty[i];
	}
	hf = copy.hf;
}

template<typename T>
HashTable<T>::~HashTable()
{
	delete[]m_keys;
	delete[]m_values;
	delete[]m_empty;
}

template<typename T>
void HashTable<T>::addKey(int key, T value)
{
	int index = 0;
	while (true)
	{
		int hash = hf->hash(index, key, m_size);
		std::cout << "hash = " << hash << std::endl;
		if (m_empty[hash])
		{
			m_keys[hash] = key;
			m_values[hash] = value;
			m_empty[hash] = false;
			return;
		}
		else if (m_keys[hash] == key)
		{
			return;
		}
		else if (m_keys[hash] != key)
		{
			index++;
		}
	}
}

template<typename T>
void HashTable<T>::deleteKey(int key, T value)
{
	if (checkKey(key, value))
	{
		bool foundIndex = false;
		int index = 0;
		int hash;
		while (!foundIndex)
		{
			hash = hf->hash(index, key, m_size);
			if (m_empty[hash])
			{
				return;
			}
			else if (m_keys[hash] == key)
			{
				if (m_values[hash] == value)
				{
					foundIndex = true;
				}
				else
				{
					return;
				}
			}
			else if (m_keys[hash] != key)
			{
				index++;
			}
		}
		int tempIndex = hash;
		bool foundNext = true;
		index++;
		while (foundNext)
		{
			hash = hf->hash(index, key, m_size);
			if (!m_empty[hash])
			{
				m_keys[tempIndex] = m_keys[hash];
				m_values[tempIndex] = m_values[hash];
				tempIndex = hash;
				index++;
			}
			else
			{
				foundNext = false;
				m_keys[tempIndex] = 0;
				m_values[tempIndex] = T();
				m_empty[tempIndex] = true;
			}
		}
	}
}

template<typename T>
bool HashTable<T>::checkKey(int key, T value)
{
	int index = 0;
	int hash;
	while (true)
	{
		hash = hf->hash(index, key, m_size);
		if (m_empty[hash])
		{
			return false;
		}
		else if (m_keys[hash] == key)
		{
			if (m_values[hash] == value)
			{
				return true;
			}
			return false;
		}
		else if (m_keys[hash] != key)
		{
			index++;
		}
	}
	return false;
}

template<typename T>
void HashTable<T>::changeHashFunction(IHashFunctions* newHashFunction)
{
	hf = newHashFunction;
	HashTable temp(m_size);
	for (int i = 0; i < m_size; i++)
	{
		if (!m_empty[i])
		{
			temp.addKey(m_keys[i], m_values[i]);
		}
	}
	*this = temp;
}

template<typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht)
{
	if (&ht == this)
	{
		return *this;
	}
	if (m_size != ht.m_size)
	{
		m_size = ht.m_size;
		if (m_keys)
		{
			delete[]m_keys;
		}
		m_keys = new int[m_size];
		if (m_values)
		{
			delete[]m_values;
		}
		m_values = new T[m_size];
		if (m_empty)
		{
			delete[]m_empty;
		}
		m_empty = new bool[m_size];
	}
	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = ht.m_keys[i];
		m_values[i] = ht.m_values[i];
		m_empty[i] = ht.m_empty[i];
	}
	return *this;
}

template<typename T>
void HashTable<T>::print()
{
	for (int i = 0; i < m_size; i++)
	{
		if (!m_empty[i])
		{
			std::cout << m_keys[i] << " : '" << m_values[i] << "'";
			std::cout << std::endl;
		}
	}
}



