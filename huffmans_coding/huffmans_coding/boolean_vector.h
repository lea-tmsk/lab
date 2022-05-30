#pragma once
#include <iostream>
using namespace std;

typedef unsigned char byte;

class BooleanVector
{
public:
	BooleanVector();
	BooleanVector(int size, int num = 0);
	BooleanVector(const char *array);
	BooleanVector(const BooleanVector& copy);
	~BooleanVector();
	void inverse_all();
	void inverse_bit(int bit);
	void set_bit(int num, int bit, int amount = 1);
	void set_all(int num);
	int weight();
	int get_size();
	void resize(int newSize);
	void filePrint(const char* fileName);
	void getFromFile(const char* fileName);

	BooleanVector operator&(const BooleanVector& bv);
	void operator&=(const BooleanVector& bv);
	BooleanVector operator|(const BooleanVector& bv);
	void operator|=(const BooleanVector& bv);
	BooleanVector operator^(const BooleanVector& bv);
	void operator^=(const BooleanVector& bv);
	BooleanVector operator<<(int amount);
	void operator<<=(int amount);
	BooleanVector operator>>(int amount);
	void operator>>=(int amount);
	BooleanVector operator~();
	void operator=(const BooleanVector& bv);
	int operator[](int const& bit) const;
	BooleanVector operator/(const BooleanVector& bv);
	void operator/=(const BooleanVector& bv);
	bool operator==(const BooleanVector& bv);

	friend ostream& operator<<(ostream &os, const BooleanVector& v);
	friend istream& operator>>(istream &is, BooleanVector& v);

	byte* vector;
	int m_size;
	int m_memory;
};

