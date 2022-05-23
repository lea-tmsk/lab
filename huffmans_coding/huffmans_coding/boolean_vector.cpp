#include "boolean_vector.h"
#include <fstream>
#include <vector>

BooleanVector::BooleanVector()
{
	m_size = 0;
	m_memory = 1;
	vector = new byte[m_memory];
	vector[0] = 0;
}

BooleanVector::BooleanVector(int size, int num)
{
	if (size < 0)
	{
		throw "Boolean vector: size < 0";
	}
	m_size = size;
	m_memory = (m_size - 1) / 8 + 1;
	vector = new byte[m_memory];
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}
	if (!num)
	{
		return;
	}
	if (num == 1)
	{
		byte mask = 1;
		int vector_index = m_memory - 1;
		for (int i = m_size - 1; i >= 0; i--, mask <<= 1)
		{
			if (!mask)
			{
				mask = 1;
				vector_index--;
			}
			vector[vector_index] |= mask;
		}
		return;
	}
	throw "\nBoolean vector: wrong number(not 1 or 0)";
}

BooleanVector::BooleanVector(const char* array)
{
	for (int i = 0; i < strlen(array); i++)
	{
		if (array[i] != '0' && array[i] != '1')
		{
			throw "\nBoolean vector: not all symbols are '0' or '1'";
		}
	}
	m_size = strlen(array);
	m_memory = (m_size - 1) / 8 + 1;
	vector = new byte[m_memory];
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}
	byte mask = 1;
	int vector_index = m_memory - 1;
	for (int i = m_size - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			vector_index--;
		}
		if (array[i] == '1')
		{
			vector[vector_index] |= mask;
		}
	}
}

BooleanVector::BooleanVector(const BooleanVector& copy)
{
	m_size = copy.m_size;
	m_memory = copy.m_memory;
	vector = new byte[m_memory];
	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] |= copy.vector[i];
	}
}

BooleanVector::~BooleanVector()
{
	delete[]vector;
}

void BooleanVector::inverse_all()
{
	int amount = m_memory * 8 - m_size;
	for (int i = m_memory - 1; i >= 0; i--)
	{
		vector[i] = ~vector[i];
	}
	vector[0] <<= amount;
	vector[0] >>= amount;
}

void BooleanVector::inverse_bit(int bit)
{
	if (bit < 0 || bit > m_size)
	{
		return;
	}
	int index_vector = m_memory - 1 - bit / 8;
	byte mask = 1;
	mask <<= bit % 8;
	if (vector[index_vector] & mask)
	{
		vector[index_vector] &= (~mask);
	}
	else
	{
		vector[index_vector] |= mask;
	}
}

void BooleanVector::set_bit(int num, int bit, int amount)
{
	if (bit < 0 || bit > m_size || amount > bit + 1)
	{
		cout << "\nset_bit: wrong bit";
		return;
	}
	int index_vector = m_memory - 1 - bit / 8;
	byte mask = 1;
	mask <<= bit % 8;
	if (!num)
	{
		for (int i = 0; i < amount; i++, mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
				index_vector++;
			}
			vector[index_vector] &= (~mask);
		}
		return;
	}
	if (num == 1)
	{
		for (int i = 0; i < amount; i++, mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
				index_vector++;
			}
			vector[index_vector] |= mask;
		}
		return;
	}
	cout << "\nset_bit: wrong number (not 1 or 0)";
	return;
}

void BooleanVector::set_all(int num)
{
	set_bit(num, m_size - 1, m_size);
}

int BooleanVector::weight()
{
	byte mask;
	int count = 0;
	for (int i = 0; i < m_memory; i++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!mask)
			{
				mask = 1 << 7;
			}
			if (vector[i] & mask)
			{
				count++;
			}
		}
	}
	return count;
}

int BooleanVector::get_size()
{
	return m_size;
}

void BooleanVector::resize(int newSize)
{
	if (newSize == m_size)
	{
		return;
	}
	if (newSize > m_memory * 8)
	{
		BooleanVector temp(*this);
		delete[]vector;
		m_size = newSize;
		m_memory = (m_size - 1) / 8 + 1;
		vector = new byte[m_memory];
		for (int i = temp.m_memory - 1; i >= 0; i--)
		{
			vector[i] = 0;
			vector[i] |= temp.vector[i];
		}
		for (int i = temp.m_memory - 1; i < m_memory; i++)
		{
			vector[i] = 0;
		}
	}
	else
	{
		BooleanVector temp(*this);
		delete[]vector;
		m_size = newSize;
		m_memory = (m_size - 1) / 8 + 1;
		vector = new byte[m_memory];
		set_all(1);
		(*this) &= temp;
	}
}

void BooleanVector::filePrint(const char* fileName)
{
	ofstream file(fileName);
	if (!file.is_open())
	{
		return;
	}

	int add = m_size % 8;
	if (add)
	{
		m_size += add;
	}

	set_bit(1, m_size - 1, add);

	file << add << " ";

	for (int i = 0 ; i < m_memory; i++)
	{
		file << vector[i];
	}
	file.close();
}

void BooleanVector::getFromFile(const char* fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		return;
	}

	int extraCode;
	file >> extraCode;
	file.get();

	std::vector<char> symbols;

	while (!file.eof())
	{
		char symbol = file.get();
		if (!file.eof())
		{
			symbols.push_back(symbol);
		}
	}
	//cout << endl << symbols.size() << endl;
	/*for (int i = 0; i < symbols.size(); i++)
	{
		cout << symbols[i] << endl;
	}*/

	if (vector)
	{
		delete[]vector;
	}
	m_memory = symbols.size();
	vector = new byte[m_memory];
	m_size = m_memory * 8 - extraCode;

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = symbols[i];
	}
	//cout << *this << endl;

	file.close();
}

void BooleanVector::operator=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator =: the same vector";
		return;
	}
	if (vector)
	{
		delete[]vector;
	}

	m_size = bv.m_size;
	m_memory = bv.m_memory;
	vector = new byte[m_memory];

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] = 0;
	}

	for (int i = 0; i < m_memory; i++)
	{
		vector[i] |= bv.vector[i];
	}
}

BooleanVector BooleanVector::operator&(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &: the same vector";
		return *this;
	}

	int size, memory;
	if (m_size > bv.m_size)
	{
		size = bv.m_size;
		memory = bv.m_memory;
	}
	else
	{
		size = m_size;
		memory = m_memory;
	}

	BooleanVector temp(size, 0);
	//int index_vector;
	for (int i = m_memory, index_vector = bv.m_memory; memory >= 0;)
	{
		temp.vector[memory--] = vector[i--] & bv.vector[index_vector--];
	}
	return temp;
}

void BooleanVector::operator&=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	BooleanVector temp = (*this & bv);
	*this = temp;
}

BooleanVector BooleanVector::operator|(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &: the same vector";
		return *this;
	}

	int size, memory, min_memory;
	bool flag;
	if (m_size > bv.m_size)
	{
		size = m_size;
		memory = m_memory - 1;
		min_memory = bv.m_memory - 1;
		flag = true;
	}
	else
	{
		size = bv.m_size;
		memory = bv.m_memory - 1;
		min_memory = m_memory - 1;
		flag = false;
	}
	BooleanVector temp(size);
	int i, index_vector;
	for (i = min_memory, index_vector = memory; i >= 0; i--, index_vector--)
	{
		if (flag)
		{
			temp.vector[index_vector] = vector[index_vector] | bv.vector[i];
		}
		else
		{
			temp.vector[index_vector] = vector[i] | bv.vector[index_vector];
		}
	}
	for (i = index_vector; i >= 0; i--)
	{
		if (flag)
		{
			temp.vector[i] |= vector[i];
		}
		else
		{
			temp.vector[i] |= bv.vector[i];
		}
	}

	return temp;
}



void BooleanVector::operator|=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	BooleanVector temp = (*this | bv);
	*this = temp;
}

BooleanVector BooleanVector::operator^(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &: the same vector";
		return *this;
	}

	int size, memory, min_memory;
	bool flag;
	if (m_size > bv.m_size)
	{
		size = m_size;
		memory = m_memory - 1;
		min_memory = bv.m_memory - 1;
		flag = true;
	}
	else
	{
		size = bv.m_size;
		memory = bv.m_memory - 1;
		min_memory = m_memory - 1;
		flag = false;
	}
	BooleanVector temp(size);
	int i, index_vector;
	for (i = min_memory, index_vector = memory; i >= 0; i--, index_vector--)
	{
		if (flag)
		{
			temp.vector[index_vector] = vector[index_vector] ^ bv.vector[i];
		}
		else
		{
			temp.vector[index_vector] = vector[i] ^ bv.vector[index_vector];
		}
	}
	for (i = index_vector; i >= 0; i--)
	{
		if (flag)
		{
			temp.vector[i] ^= vector[i];
		}
		else
		{
			temp.vector[i] ^= bv.vector[i];
		}
	}

	return temp;
}

void BooleanVector::operator^=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	BooleanVector temp = (*this ^ bv);
	*this = temp;
}

BooleanVector BooleanVector::operator<<(int amount)
{
	BooleanVector temp(*this);
	temp <<= amount;
	return temp;
}

void BooleanVector::operator<<=(int amount)
{
	if (!amount)
	{
		return;
	}
	if (!m_memory)
	{
		cout << "\noperator <<=: the size of vector is 0";
		return;
	}
	int bit = m_size + amount;
	if (bit / 8 + 1 > m_memory)
	{
		while (bit / 8 + 1 > m_memory)
		{
			bit--;
		}
		m_size = bit + 1;
	}
	else
	{
		m_size = bit;
	}
	for (int i = bit - amount; i >= 0; i--, bit--)
	{
		if (operator[](i))
		{
			set_bit(1, bit);
		}
		else
		{
			set_bit(0, bit);
		}
	}
	set_bit(0, amount - 1, amount);
}

//void BooleanVector::operator<<=(int amount)
//{
//	if (!m_memory)
//	{
//		cout << "\noperator <<=: the size of vector is 0";
//		return;
//	}
//	if (m_size > m_memory * 8)
//	{
//		BooleanVector temp = *this;
//		m_size += amount;
//		//cout << "temp > memory: " << temp << endl;
//		delete[]vector;
//		m_memory = (m_size - 1) / 8 + 1;
//		vector = new byte[m_memory];
//		for (int i = 0; i < m_memory; i++)
//		{
//			vector[i] = 0;
//		}
//		for (int i = temp.m_memory - 1, j = 1; i >= 0; i--, j++)
//		{
//			vector[m_memory - j] |= temp.vector[i] << amount % 8;
//			if (i > 0)
//			{
//				vector[m_memory - j] |= (temp.vector[i - 1] >> (8 - (amount % 8)));
//			}
//		}
//	}
//	else
//	{
//		BooleanVector temp = *this;
//		m_size += amount;
//		//cout << "temp < memory: " << temp << endl;
//		for (int i = temp.m_memory - 1, j = 1; i >= 0; i--, j++)
//		{
//			cout << (temp.vector[i] << amount) << endl;
//			vector[m_memory - j] |= (temp.vector[i] << amount);
//			if (i > 0)
//			{
//				vector[m_memory - j] |= (temp.vector[i - 1] >> (8 - amount % 8));
//			}
//		}
//	}
//	set_bit(0, amount - 1, amount);
//}

BooleanVector BooleanVector::operator>>(int amount)
{
	BooleanVector temp(*this);
	temp >>= amount;
	return temp;
}

void BooleanVector::operator>>=(int amount)
{
	if (!m_memory)
	{
		cout << "\noperator >>=: the size of vector is 0";
		return;
	}
	int i, bit = amount;
	for (i = 0; bit < m_size; i++, bit++)
	{
		if ((*this)[bit])
		{
			set_bit(1, i);
		}
		else
		{
			set_bit(0, i);
		}
	}
	set_bit(0, m_size - 1, amount);
	m_size = m_size - amount;
}

BooleanVector BooleanVector::operator~()
{
	BooleanVector temp(*this);
	temp.inverse_all();
	return temp;
}

int BooleanVector::operator[](int const& bit) const
{
	if (bit < 0 || bit > m_size)
	{
		throw "\nopeartor []: wrong bit";
	}
	int index_vector = m_memory - 1 - bit / 8;
	byte mask = 1;
	mask <<= bit % 8;
	if (vector[index_vector] & mask)
	{
		return 1;
	}
	return 0;
}

BooleanVector BooleanVector::operator/(const BooleanVector& bv)
{
	if (this == &bv)
	{
		BooleanVector temp(m_size, 0);
		return temp;
	}
	//BooleanVector temp;
	//temp = *this | bv;
	BooleanVector temp(*this);
	temp &= ~(*this & bv);
	return temp;
}

void BooleanVector::operator/=(const BooleanVector& bv)
{
	if (&bv == this)
	{
		cout << "\noperator &=: the same vector";
		return;
	}
	*this = (*this / bv);
}

bool BooleanVector::operator==(const BooleanVector& bv)
{
	if (m_size != bv.m_size)
	{
		return false;
	}
	for (int i = 0; i < m_memory; i++)
	{
		if ((vector[i] & bv.vector[i]) != vector[i])
		{
			return false;
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const BooleanVector& bv)
{
	byte mask;
	bool flag = true;
	for (int i = 0; i < bv.m_memory; i++)
	{
		for (mask = 1 << 7; mask; mask >>= 1)
		{
			if (!i && flag)
			{
				mask = 1 << bv.m_size % 8 - 1;
				flag = false;
			}
			if (!mask)
			{
				mask = 1 << 7;
			}
			if (bv.vector[i] & mask)
			{
				os << '1';
			}
			else
			{
				os << '0';
			}
		}
	}
	return os;
}

istream& operator>>(istream& is, BooleanVector& bv)
{
	if (bv.vector)
	{
		delete[]bv.vector;
	}
	char* string;
	string = new char[INT16_MAX];
	cin >> string;

	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] != '0' && string[i] != '1')
		{
			throw "\noperator>>: not all symbols are '0' or '1'";
		}
	}

	bv.m_size = strlen(string);
	bv.m_memory = (bv.m_size - 1) / 8 + 1;
	bv.vector = new byte[bv.m_memory];
	for (int i = 0; i < bv.m_memory; i++)
	{
		bv.vector[i] = 0;
	}

	byte mask = 1;
	int index_vector = bv.m_memory - 1;
	for (int i = bv.m_size - 1; i >= 0; i--, mask <<= 1)
	{
		if (!mask)
		{
			mask = 1;
			index_vector--;
		}
		if (string[i] == '1')
		{
			bv.vector[index_vector] |= mask;
		}

	}
	delete[]string;
	return is;
}