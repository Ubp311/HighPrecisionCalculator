#pragma once
#include	<iostream>
#include	<string>


using namespace std;

union value
{
	int* intValPtr = nullptr;
	double* floatValPtr;
};

class ExRange
{
private:
	value val;
	size_t	size;
	size_t	capacity;
	bool	isInt;
public:
	ExRange();
	ExRange(int	val);
	ExRange(double val);
	ExRange(const ExRange& _val);
	~ExRange();

	int	clear();
	ExRange	at(size_t index);
	int	resize(size_t size);
	size_t	getSize();
	size_t	getCapacity();
	bool	getIsInt();
	bool	empty();
	int	pushBack(int val);
	int	pushBack(double val);
	int	popBack();

	ExRange operator=(const ExRange& _val);
	ExRange	operator[](size_t index);

	ExRange static intEncode(const string valStr);
	ExRange static doubleEncode(const string valStr);
	string	static decode(ExRange& _val);

	ExRange& operator*(int val);
	ExRange& operator/(int val);
	ExRange& operator%(int val);
	ExRange& operator+(int val);
	ExRange& operator-(int val);
	bool	operator==(int val);
	bool	operator!=(int val);
	bool	operator>=(int val);
	bool	operator<=(int val);
	bool	operator>(int val);
	bool	operator<(int val);

	ExRange& operator*(double val);
	ExRange& operator/(double val);
	ExRange& operator+(double val);
	ExRange& operator-(double val);
	bool	operator==(double val);
	bool	operator!=(double val);
	bool	operator>=(double val);
	bool	operator<=(double val);
	bool	operator>(double val);
	bool	operator<(double val);

	ExRange& operator*(ExRange& _val);
	ExRange& operator/(ExRange& _val);
	ExRange& operator%(ExRange& _val);
	ExRange& operator+(ExRange& _val);
	ExRange& operator-(ExRange& _val);
	bool	operator==(ExRange& _val);
	bool	operator!=(ExRange& _val);
	bool	operator>=(ExRange& _val);
	bool	operator<=(ExRange& _val);
	bool	operator>(ExRange& _val);
	bool	operator<(ExRange& _val);
};