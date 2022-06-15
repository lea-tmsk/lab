#include <math.h>
#include <iostream>
#pragma once

class IHashFunctions
{
public:
	virtual int hash(int index, int key, int size) = 0;
};

class HashFunction1 : public IHashFunctions
{
public:
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

class HashFunction2 : public IHashFunctions
{
public:
	int hash(int index, int key, int size) override
	{
		int hash = key % size;
		double a = -(1 - sqrt(5)) / 2;
		for (int i = 0; i < index; i++)
		{
			hash = ((int)(hash * a * size) + 1) % size;
		}
		return hash;
	}
} hf2;

class HashFunction : public IHashFunctions
{
public:
	int hash(int index, int key, int size) override
	{
		return (key % size + index * (1 + key % abs(size - 2))) % size;
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

	bool addKey(int key, T value);
	bool deleteKey(int key);
	bool checkKey(int key);
	void changeHashFunction(IHashFunctions* newHashFunction);

	HashTable<T>& operator=(const HashTable<T>& ht);

	void print();

private:
	IHashFunctions* hf;
	int m_actual_size = 0;
	int m_size;
	int* m_keys;
	T* m_values;
	enum state
	{
		empty,
		filled,
		deleted
	} * m_states;
};



template<typename T>
HashTable<T>::HashTable()
{
	m_size = 1;
	m_keys = new int[m_size];
	m_values = new T[m_size];
	m_states = new state[m_size];
	m_keys[0] = 0;
	m_values[0] = T();
	m_states[0] = empty;
	hf = &hf1;
}

template<typename T>
HashTable<T>::HashTable(int size)
{
	m_size = size;
	m_keys = new int[m_size];
	m_values = new T[m_size];
	m_states = new state[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = 0;
		m_values[i] = T();
		m_states[i] = empty;
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
		
		if (m_states)
		{
			delete[]m_states;
		}
		m_states = new bool[m_size];
	}

	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = copy.m_keys[i];
		m_values[i] = copy.m_values[i];
		m_states[i] = copy.m_states[i];
	}
	hf = copy.hf;
}

template<typename T>
HashTable<T>::~HashTable()
{
	delete[]m_keys;
	delete[]m_values;
	delete[]m_states;
}

template<typename T>
bool HashTable<T>::addKey(int key, T value)
{
	if (m_actual_size + 1 > m_size)
	{
		return false;
	}
	if (checkKey(key))
	{
		return false;
	}

	m_actual_size++;
	int index = 0;
	while (true)
	{
		int hash = hf->hash(index, key, m_size);
		if (m_states[hash] != filled)
		{
			m_keys[hash] = key;
			m_values[hash] = value;
			m_states[hash] = filled;
			return true;
		}
		else if (m_keys[hash] != key)
		{
			index++;
		}
	}
}

template<typename T>
bool HashTable<T>::deleteKey(int key)
{
	if (checkKey(key))
	{
		m_actual_size--;
		int index = 0;
		while (true)
		{
			int hash = hf->hash(index, key, m_size);
			if (m_states[hash] == empty)
			{
				return false;
			}
			else if (m_keys[hash] == key)
			{
				m_states[hash] = deleted;
				return true;
			}
			else if (m_keys[hash] != key)
			{
				index++;
			}
		}
	}
	return false;
}

template<typename T>
bool HashTable<T>::checkKey(int key)
{
	int index = 0;
	int hash;
	while (true)
	{
		hash = hf->hash(index, key, m_size);
		if (m_states[hash] == empty)
		{
			return false;
		}
		else if (m_keys[hash] == key)
		{
			return true;
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
	temp.hf = newHashFunction;
	for (int i = 0; i < m_size; i++)
	{
		if (m_states[i] != empty)
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
		
		if (m_states)
		{
			delete[]m_states;
		}
		m_states = new state[m_size];
	}
	for (int i = 0; i < m_size; i++)
	{
		m_keys[i] = ht.m_keys[i];
		m_values[i] = ht.m_values[i];
		m_states[i] = ht.m_states[i];
	}
	return *this;
}

template<typename T>
void HashTable<T>::print()
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_states[i] == filled)
		//if (m_states[i] != empty)
		{
			std::cout << "(" << i << ") ";
			std::cout << m_keys[i] << " : '" << m_values[i] << "'";
			//std::cout << ((m_states[i] == filled) ? " filled" : " deleted");
			std::cout << std::endl;
		}
	}
}



