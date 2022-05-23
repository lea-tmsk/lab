#include "boolean_vector.h"
#pragma once

class Set : public BooleanVector
{
public:
	Set();
	Set(const char *string);
	Set(const Set &copy);
	~Set() {};

	void print() const;
	bool check_element(char ch);
	int get_max();
	int get_min();
	int get_power();

	//using BooleanVector::operator=;
	//using BooleanVector::operator[];

	void operator=(const Set &set);
	bool operator==(const Set &set);
	bool operator!=(const Set &set);
	Set operator|(const Set &set);
	void operator|=(const Set &set);
	Set operator&(const Set &set);
	void operator&=(const Set &set);
	Set operator/(const Set &set);
	void operator/=(const Set &set);
	Set operator~();
	Set operator+(const char ch);
	void operator+=(const char ch);
	Set operator-(const char ch);
	void operator-=(const char ch);

	friend ostream& operator<<(ostream &os, const Set &set);
	friend istream& operator>>(istream &is, Set &set);
private:
	int m_power; //мощность
};

