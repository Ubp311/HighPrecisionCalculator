#pragma once
#include	<iostream>
#include	<vector>
#include	"ExRange.h"


using namespace std;

struct complexValue
{
	ExRange realVal, imaginVal;
};

typedef ExRange	realValue;

typedef vector<complexValue> values;

class Calc
{
private:
	values mem;
public:
	complexValue static calculate(values& vals, vector<char> vOp);
	bool	divisibility(char op, ExRange val1, ExRange val2);
	bool	divisibility(char op, ExRange val1, int val2);
	bool	divisibility(char op, ExRange val1, double val2);
	bool	divisibility(char op, int val1, ExRange val2);
	bool	divisibility(char op, double val1, ExRange val2);
	bool	divisibility(char op, int val1, int val2);
	bool	divisibility(char op, double val1, int val2);
	bool	divisibility(char op, int val1, double val2);
	bool	divisibility(char op, double val1, double val2);

	realValue factorial(int val);
	complexValue factorial(float val);
	realValue factorial(const realValue& val);
	complexValue factorial(const complexValue& val);
	realValue permutation(int val);
	realValue permutation(const complexValue& val);
};

