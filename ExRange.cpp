#include "ExRange.h"


using namespace std;

const unsigned int kIntLimit = 2147483648U;
const int kIntParseLimit = 100000000;
const int kIntParseLimitDigitNum = 8;
const long long	kUIntMaxLimit = 4294697295LL;

string itoa(int val)
{
	string	resultStr;

	if (val == 0)
		return	"0";

	int sign = 1;

	if (val < 0)
		sign = -1;

	int	tempVal = val * sign;
	int mul = 1;

	while (tempVal != 0)
	{
		tempVal /= 10;
		mul *= 10;
	}
	tempVal = val * sign;
	if (sign == -1)
		resultStr += '-';
	while (mul != 1)
	{
		tempVal %= mul;
		mul /= 10;
		resultStr += tempVal / mul + '0';
	}

	return	resultStr;
};

int	positiveFloor(double val)
{
	if (val > 0.0)
		return (val != (int)val) ? val : val - 1;
	else
		return 0;
};

int	myCeil(double val)
{
	return val + ((int)val - val);
};

int myFloor(double val)
{
	return (int(((val >= 0) || (val == (int)val))) ? val : val - 1);
};

ExRange::ExRange()
{
	val.intValPtr = nullptr;
	size = 0;
	capacity = 0;
	isInt = true;
}

ExRange::ExRange(int _val)
{
	val.intValPtr = new int[1];
	val.intValPtr[0] = _val;
	size = 1;
	capacity = 1;
	isInt = true;
}

ExRange::ExRange(double _val)
{
	val.floatValPtr = new double[1];
	val.floatValPtr[0] = _val;
	size = 1;
	capacity = 1;
	isInt = false;
}

ExRange::ExRange(const ExRange& _val)
{
	if (!_val.isInt)
	{
		val.floatValPtr = new double[_val.capacity];
		size = _val.size;
		capacity = _val.size;
		copy(val.floatValPtr, val.floatValPtr + size - 1, _val.val.floatValPtr);
		isInt = false;
	}
	else
	{
		val.intValPtr = new int[_val.capacity];
		size = _val.size;
		capacity = _val.size;
		copy(val.intValPtr, val.intValPtr + size - 1, _val.val.intValPtr);
		isInt = false;
	}
}

ExRange::~ExRange()
{
	if (!isInt)
		delete[] val.floatValPtr;
	else
		delete[] val.intValPtr;
}

int	ExRange::clear()
{
	if (!isInt)
	{
		delete[] val.floatValPtr;
		val.floatValPtr = new double[1]();
	}
	else
	{
		delete[] val.intValPtr;
		val.intValPtr = new int[1]();
	}
	size = 1;
	capacity = 1;

	return	0;
}

ExRange	ExRange::at(size_t index)
{
	if (!isInt)
		return val.floatValPtr[index];
	return val.intValPtr[index];
}

int	ExRange::resize(size_t _size)
{
	if (!isInt)
	{
		
	}
	else
	{
		int* tempIntValPtr;

		if (capacity < _size)
		{
			tempIntValPtr = new int[_size];
			copy(val.intValPtr, val.intValPtr + size - 1, tempIntValPtr);
			delete[] val.intValPtr;
			val.intValPtr = tempIntValPtr;
		}
		else
			size = _size;
	}
	capacity = _size;

	return	0;
}

size_t	ExRange::getSize()
{
	return	size;
}

size_t	ExRange::getCapacity()
{
	return capacity;
}

bool	ExRange::getIsInt()
{
	return	isInt;
}

bool	ExRange::empty()
{
	if (size > 0)
		return false;
	return true;
}

int	ExRange::pushBack(int _val)
{
	if (!isInt)
	{
		double* tempFloatValPtr;
		if (size >= capacity)
		{
			capacity *= 2;
			tempFloatValPtr = new double[capacity];
			copy(val.floatValPtr, val.floatValPtr + size - 1, tempFloatValPtr);
			delete[] val.floatValPtr;
			val.floatValPtr = tempFloatValPtr;
		}
		val.floatValPtr[size++] = _val;

	}
	else
	{
		int* tempIntValPtr;
		if (size >= capacity)
		{
			capacity *= 2;
			tempIntValPtr = new int[capacity];
			copy(val.intValPtr, val.intValPtr + size - 1, tempIntValPtr);
			delete[] val.intValPtr;
			val.intValPtr = tempIntValPtr;
		}
		val.intValPtr[size++] = _val;
	}

	return	0;
}

int ExRange::pushBack(double _val)
{
	if (!isInt)
	{
		double* tempFloatValPtr;
		if (size >= capacity)
		{
			capacity *= 2;
			tempFloatValPtr = new double[capacity];
			copy(val.floatValPtr, val.floatValPtr + size, tempFloatValPtr);
			delete[] val.floatValPtr;
			val.floatValPtr = tempFloatValPtr;
		}
		val.floatValPtr[size++] = _val;

		return	0;
	}
	else
	{
		cout << "Warning : Casting from double to int." << endl;
		int* tempIntValPtr;
		if (size >= capacity)
		{
			capacity *= 2;
			tempIntValPtr = new int[capacity];
			copy(val.intValPtr, val.intValPtr + size - 1, tempIntValPtr);
			delete[] val.intValPtr;
			val.intValPtr = tempIntValPtr;
		}
		val.intValPtr[size++] = _val;

		return	1;
	}
}

int	ExRange::popBack()
{
	if (size > 0)
		size--;
	else
		return -1;
	return 0;
}



ExRange	ExRange::operator=(const ExRange& _val)
{
	if (!isInt)
		delete[] val.intValPtr;
	else
		delete[] val.floatValPtr;
	isInt = _val.isInt;
	if (!isInt)
	{
		val.intValPtr = new int[_val.capacity];
		copy(_val.val.intValPtr, _val.val.intValPtr + _val.size - 1, val.intValPtr);
	}
	else
	{
		val.floatValPtr = new double[_val.capacity];
		copy(_val.val.floatValPtr, _val.val.floatValPtr + _val.size - 1, val.floatValPtr);
	}
	size = _val.size;
	capacity = _val.capacity;

	return	*this;
}

ExRange	ExRange::operator[](size_t index)
{
	if (index >= size && index < capacity)
		cout << "Warning : Accessing uninitialized area." << endl;
	else
	{
		cout << "Error : Accesssing unallocated area." << endl;
		return	ExRange();
	}

	if (!isInt)
		return ExRange(val.floatValPtr[index]);
	else
		return ExRange(val.intValPtr[index]);
}

ExRange	ExRange::intEncode(string valStr)
{
	ExRange	result;

	size_t size = 1;
	size_t capacity = 1;
	
	unsigned long long	tempVal;

	string tempValStr;

	unsigned int i = 0;

	int	sign = 1;

	int isSigned = 0;

	result.pushBack(0);
	while (valStr.compare("0"))
	{
		i = 0;
		tempVal = 0ULL;

		isSigned = 0;

		if (valStr[0] == '-')
		{
			sign = -1;
			isSigned = 1;
		}
		for (; i <= kIntParseLimit + isSigned && i < valStr.size(); i++)
			tempVal = tempVal * 10ULL + valStr[i] - '0';
		for (; i < valStr.size(); i++)
		{
			tempVal = tempVal * 10ULL + valStr[i] - '0';
			tempValStr += tempVal / kIntLimit + '0';
			tempVal %= kIntLimit;
		}
		if (kIntParseLimitDigitNum + 1 + isSigned >= valStr.size())
			tempValStr = "0";
		result.pushBack(sign * (int)tempVal);
		valStr = tempValStr;
		tempValStr.clear();
	}
	
	return	result;
}

ExRange	ExRange::doubleEncode(const string valStr)
{
	// -23437248.7398718E-4321748

	ExRange	result;

	string	expStr;
	string	fracStr;

	ExRange	frac(0);
	ExRange exp(0);

	unsigned int i = 0;

	int	sign = 1;
	int expSign = 1;
	int decExp = 0;

	bool	isDot = false;

	if (valStr[i] == '-')
	{
		sign = -1;
		i++;
	}
	for (; i < valStr.size() && valStr[i] != 'E'; i++)
	{
		if (valStr[i] >= '0' && valStr[i] <= '9')
			fracStr += valStr[i];
		else if (valStr[i] == '.')
		{
			decExp = i - 1;
			isDot = true;
		}
	}
	if (!isDot)
		decExp = i - 1;
	if (valStr[i] == 'E')
	{
		i++;
		if (valStr[i] == '-')
		{
			expSign = -1;
			i++;
		}
		for (; i < valStr.size(); i++)
		{
			if (valStr[i] >= '0' && valStr[i] <= '9')
				expStr += valStr[i];
		}
	}

	exp = intEncode(expStr) + decExp;
	frac = intEncode(fracStr);

	// These code are test script, alternative code required.
}

string	ExRange::decode(ExRange& _val)
{
	string resultStr;

	size_t i = 0;
	size_t j = 0;

	if (_val.isInt)
	{
		
	}
	else
	{
		ExRange	resultVal(0), tempResultVal;
		ExRange	mulVal(1), tempMulVal, baseVal;
		ExRange& mulValRef = mulVal, &tempMulValRef = tempMulVal;
		int tempResultFinalIndex = 0;

		int sign = 1;

		int carry = 0;
		long long	mul;
		int	add;

		long long	_valArr[2] = { 0LL, };

		baseVal.pushBack((int)(kIntLimit % kIntParseLimit));
		baseVal.pushBack((int)(kIntLimit / kIntParseLimit));

		if (_val[_val.size - 1] < 0)
			sign = -1;
		for (i = 0; i < _val.size; i++)
		{
			tempResultFinalIndex = 0;
			_valArr[0] = _val.val.intValPtr[i] * sign % kIntParseLimit;
			_valArr[1] = _val.val.intValPtr[i] * sign / kIntParseLimit;
			for (j = 0; j < mulVal.size; j++)
			{
				carry = 0;
				for (size_t k = 0; k < 2; k++)
				{
					mul = _valArr[k] * mulVal.val.intValPtr[j] + carry;
					carry = mul / kIntParseLimit;
					mul %= kIntParseLimit;
					if (mul != 0)
						tempResultFinalIndex = j + k;
					if (j + k == tempResultVal.size)
						tempResultVal.pushBack(0);
					carry += (tempResultVal.val.intValPtr[j + k] + mul) / kIntParseLimit;
					tempResultVal.val.intValPtr[j + k] = (tempResultVal.val.intValPtr[j + k] + mul) % kIntParseLimit;
				}
				if (carry != 0)
					tempResultVal.pushBack(carry);
			}
			carry = 0;
			for (j = 0; j < resultVal.size && j < tempResultVal.size; j++)
			{
				add = resultVal.val.intValPtr[j] + tempResultVal.val.intValPtr[j] + carry;
				carry = add / kIntParseLimit;
				resultVal.val.intValPtr[j] = add % kIntParseLimit;
			}
			for (; j < tempResultVal.size; j++)
			{
				add = tempResultVal.val.intValPtr[j] + carry;
				carry = add / kIntParseLimit;
				resultVal.pushBack(add % kIntParseLimit);
			}
			for (; j < resultVal.size; j++)
			{
				add = resultVal.val.intValPtr[j] + carry;
				carry = add / kIntParseLimit;
				resultVal.val.intValPtr[j] = add % kIntParseLimit;
			}
			if (carry != 0)
				resultVal.pushBack(carry);
			for (j = 0; j < mulVal.size; j++)
			{
				carry = 0;

				for (size_t k = 0; k < 2; k++)
				{
					mul = (long long)mulValRef.val.intValPtr[j] * baseVal.val.intValPtr[k] + carry;
					carry = mul / kIntParseLimit;
					mul %= kIntParseLimit;
					if (j + k == tempMulVal.size)
						tempMulValRef.pushBack(0);
					carry += (tempMulValRef.val.intValPtr[j + k] + mul) / kIntParseLimit;
					tempMulValRef.val.intValPtr[j + k] = (tempMulValRef.val.intValPtr[j + k] + mul) % kIntParseLimit;
				}
				if (carry != 0)
					tempMulValRef.pushBack(carry);
			}
			swap(mulValRef, tempMulValRef);
			tempMulValRef.clear();
			tempResultVal.clear();
		}
		if (sign == -1)
		{
			for (i = 0; i < resultVal.size; i++)
				resultVal.val.intValPtr[i] *= -1;
		}
		resultStr += itoa(resultVal.val.intValPtr[resultVal.size - 1]);
		for (long long i = resultVal.size - 2; i >= 0; i--)
		{
			int	tempVal = resultVal.val.intValPtr[i];
			int	digitNum = 0;

			if (sign == -1)
				resultVal.val.intValPtr[i] *= -1;
			while (tempVal != 0)
			{
				tempVal /= 10;
				digitNum++;
			}
			for (j = 0; j < kIntParseLimitDigitNum - digitNum; j++)
				resultStr += '0';
			if (digitNum != 0)
				resultStr += itoa(resultVal.val.intValPtr[i]);
		}
	}

	return	resultStr;
}

ExRange&	ExRange::operator+(int _val)
{
	if (!isInt)
		;
	else
	{
		if (val.intValPtr[size - 1] >= 0 && _val >= 0 || val.intValPtr[size - 1] < 0 && _val < 0)
		{
			int	sign = 1;
			unsigned int	sum;
			int	carry = 0;

			if (val.intValPtr[size - 1] < 0)
			{
				sign = -1;
				for (size_t i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
				_val *= -1;
			}
			sum = val.intValPtr[0] + _val;
			carry = sum / kIntLimit;
			val.intValPtr[0] = sum % kIntLimit;
			for (size_t i = 0; i < size; i++)
			{
				sum = val.intValPtr[i] + carry;
				carry = sum / kIntLimit;
				val.intValPtr[i] = sum % kIntLimit;
			}
			if (carry != 0)
				pushBack(carry);
			if (sign == -1)
			{
				for (size_t i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
			}
		}
		else
		{
			size_t tempIndex = 0;
			int	carry = 0;

			val.intValPtr[0] += _val;
			if (val.intValPtr[size - 1] < 0)
			{
				for (size_t i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]++;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] > 0)
					{
						val.intValPtr[i] += kIntLimit;
						carry = 1;
					}
				}
			}
			else
			{
				for (size_t i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]--;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] < 0)
					{
						val.intValPtr[i] += kIntLimit;
						carry = -1;
					}
				}
			}
			resize(tempIndex + 1);
		}

		/*if (size == 0) //*----------		legacy code.
			val.intValPtr = new int[1]();
		int sign = 1;
		int carry = 0;
		long long	sum = 0LL;

		if (val.intValPtr[size - 1] >= 0 && _val >= 0 || val.intValPtr[size - 1] < 0 && _val < 0)
		{
			if (val.intValPtr[size - 1] < 0 && _val < 0)
			{
				sign = -1;
				for (size_t i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
				_val *= -1;
			}
			sum = val.intValPtr[0] + _val;
			carry = sum / kIntLimit;
			val.intValPtr[0] = sum % kIntLimit;
			for (size_t i = 1; i < size; i++)
			{
				sum = val.intValPtr[i] + carry;
				carry = sum / kIntLimit;
				val.intValPtr[i] = sum % kIntLimit;
			}
			if (carry != 0LL)
				pushBack(carry);
			if (sign == -1)
			{
				for (size_t i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
			}
		}
		else
		{
			size_t	i = 0;

			if (val.intValPtr[size - 1] < 0)
				sign = -1;
			if (size == 1)
				val.intValPtr[0] += _val;
			else
			{
				sum = val.intValPtr[0] + _val;
				if (sign == -1)
				{
					carry = myCeil((double)sum / kIntLimit);
					val.intValPtr[0] = (carry != 0) ? kIntLimit + sum % kIntLimit : sum;
					for (i = 1; i < size - 1; i++)
					{
						sum = val.intValPtr[i] + carry;
						carry = myCeil((double)sum / kIntLimit);
						val.intValPtr[i] = (carry != 0) ? kIntLimit + sum % kIntLimit : sum;
					}
				}
				else
				{
					carry = myFloor((double)sum / kIntLimit);
					val.intValPtr[0] = (carry != 0) ? kIntLimit + sum % (int)kIntLimit : sum;
					for (i = 1; i < size - 1; i++)
					{
						sum = val.intValPtr[i] + carry;
						carry = myFloor((double)sum / kIntLimit);
						val.intValPtr[i] = (carry != 0) ? kIntLimit + sum % (int)kIntLimit : sum;
					}
				}
				val.intValPtr[i] += carry;
				if (val.intValPtr[i] == 0)
					popBack();
			}
		} */ //-----------*
	}

	return *this;
}

ExRange&	ExRange::operator-(int _val)
{
	if (!isInt)
		;
	else
	{
		if (val.intValPtr[size - 1] >= 0 && _val >= 0 || val.intValPtr[size - 1] < 0 && _val < 0)
		{
			size_t tempIndex = 0;
			int	carry = 0;

			val.intValPtr[0] -= _val;
			if (val.intValPtr[size - 1] < 0)
			{
				for (size_t i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]++;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] > 0)
					{
						val.intValPtr += kIntLimit;
						carry = 1;
					}
				}
			}
			else
			{
				for (size_t i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]--;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] < 0)
					{
						val.intValPtr[i] += kIntLimit;
						carry = -1;
					}
				}
			}
			resize(tempIndex + 1);
		}
		else
		{
			int sign = 1;
			unsigned int	sub;
			int	carry = 0;

			if (val.intValPtr[size - 1] < 0)
			{
				sign = -1;
				for (size_t i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
				_val *= -1;
			}
			sub = val.intValPtr[0] - _val;
			carry = sub / kIntLimit;
			val.intValPtr[0] = sub % kIntLimit;
			for (size_t i = 1; i < size; i++)
			{
				sub = val.intValPtr[i] + carry;
				carry = sub / kIntLimit;
				val.intValPtr[i] = sub % kIntLimit;
			}
			if (carry != 0)
				pushBack(carry);
			if (sign != -1)
			{
				for (size_t i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
			}
		}
	}

	/*if (val.intValPtr[size - 1] >= 0 && _val >= 0 || val.intValPtr[size - 1] < 0 && _val < 0) //*--------- legacy code.
		{
			if (val.intValPtr[size - 1] < 0)
				sign = -1;
			if (size == 1)
				val.intValPtr[size - 1] -= _val;
			else
			{	//		5 - 10
				sub = val.intValPtr[0] - _val;
				if (sign == -1)
				{
					carry = myCeil((double)sub / kIntLimit);
					val.intValPtr[0] = (carry != 0) ? kIntLimit + sub % kIntLimit : sub;
					for (i = 0; i < size - 1; i++)
					{
						sub = val.intValPtr[i] + carry;
						carry = myCeil((double)sub / kIntLimit);
						val.intValPtr[i] = (carry != 0) ? kIntLimit + sub % kIntLimit : sub;
					}
				}
				else
				{
					carry = myFloor((double)sub / kIntLimit);
					val.intValPtr[0] = (carry != 0) ? kIntLimit + sub % (int)kIntLimit : sub;
					for (i = 1; i < size - 1; i++)
					{
						sub = val.intValPtr[i] + carry;
						carry = myFloor((double)sub / kIntLimit);
						val.intValPtr[i] = (carry != 0) ? kIntLimit + sub % (int)kIntLimit : sub;
					}

				}
				val.intValPtr[i] += carry;
				if (val.intValPtr[i] == 0)
					popBack();
			}
		}*/ //---------*

	return	*this;
}

ExRange&	ExRange::operator*(ExRange& _val)
{
	if (!isInt)
	{

	}
	else
	{
		ExRange	result(0);

		long long mul;
		int	carry = 0;

		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < _val.size; j++)
			{
				mul = (long long)val.intValPtr[i] * _val.val.intValPtr[j] + carry;
				carry = mul / kIntLimit;
				mul %= kIntLimit;
				if (i + j == result.size)
					result.pushBack(0);
				carry += (result.val.intValPtr[i + j] + mul) / kIntLimit;
				result.val.intValPtr[i + j] = (result.val.intValPtr[i + j] + mul) % kIntLimit;
			}
			if (carry != 0)
				result.pushBack(carry);
		}

		return	result;
	}
}

ExRange&	ExRange::operator+(ExRange& _val)
{
	size_t i = 0;

	if (!isInt)
	{

	}
	else
	{
		if (val.intValPtr[size - 1] >= 0 && _val.val.intValPtr[_val.size - 1] >= 0
			|| val.intValPtr[size - 1] < 0 && _val.val.intValPtr[_val.size - 1] < 0)
		{
			int sign = 1;
			int carry = 0;
			unsigned int	sum;

			if (val.intValPtr[size - 1] < 0)
			{
				sign = -1;
				for (; i < size; i++)
					val.intValPtr[i] *= -1;
				for (i = 0; i < _val.size; i++)
					_val.val.intValPtr[i] *= -1;
			}
			for (i = 0; i < size && i < _val.size; i++)
			{
				sum = (unsigned int)val.intValPtr[i] + _val.val.intValPtr[i] + carry;
				carry = sum / kIntLimit;
				val.intValPtr[i] = sum % kIntLimit;
			}
			for (; i < size; i++)
			{
				sum = (unsigned int)val.intValPtr[i] + carry;
				carry = sum / kIntLimit;
				val.intValPtr[i] = sum % kIntLimit;
			}
			for (; i < _val.size; i++)
			{
				sum = (unsigned int)_val.val.intValPtr[i] + carry;
				carry = sum / kIntLimit;
				pushBack((int)(sum % kIntLimit));
			}
			if (carry != 0)
				pushBack(carry);
			if (sign == -1)
			{
				for (i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
				for (i = 0; i < _val.size; i++)
					_val.val.intValPtr[i] *= -1;
			}
		}
		else
		{
			int	carry = 0;
			size_t	tempIndex = 0;

			for (; i < size && i < _val.size; i++)
				val.intValPtr[i] += _val.val.intValPtr[i];
			for (; i < _val.size; i++)
				pushBack(_val.val.intValPtr[i]);
			for (i = size - 1; i > 0; i--)
			{
				if (val.intValPtr[i] != 0)
					break;
			}
			resize(i + 1);

			if (val.intValPtr[size - 1] < 0)
			{
				for (i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]++;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] > 0)
					{
						val.intValPtr += kIntLimit;
						carry = 1;
					}
				}
			}
			else
			{
				for (i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]--;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] < 0)
					{
						val.intValPtr[i] += kIntLimit;
						carry = -1;
					}
				}
			}
			resize(tempIndex + 1);
		}
	}
	
	return	*this;
}

ExRange&	ExRange::operator-(ExRange& _val)
{
	size_t i = 0;

	if (!isInt)
	{
		if (val.intValPtr[size - 1] >= 0 && _val.val.intValPtr[_val.size - 1] >= 0
			|| val.intValPtr[size - 1] < 0 && _val.val.intValPtr[_val.size - 1] < 0)
		{
			int	carry = 0;
			size_t	tempIndex = 0;

			for (; i < size && i < _val.size; i++)
				val.intValPtr[i] += _val.val.intValPtr[i];
			for (; i < _val.size; i++)
				pushBack(_val.val.intValPtr[i]);
			for (i = size - 1; i > 0; i--)
			{
				if (val.intValPtr[i] != 0)
					break;
			}
			resize(i + 1);

			if (val.intValPtr[size - 1] < 0)
			{
				for (i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]++;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] > 0)
					{
						val.intValPtr += kIntLimit;
						carry = 1;
					}
				}
			}
			else
			{
				for (i = 0; i < size; i++)
				{
					if (carry != 0)
					{
						val.intValPtr[i]--;
						carry = 0;
					}
					if (val.intValPtr[i] != 0)
						tempIndex = i;
					if (val.intValPtr[i] < 0)
					{
						val.intValPtr[i] += kIntLimit;
						carry = -1;
					}
				}
			}
			resize(tempIndex + 1);
		}
		else
		{
			int sign = 1;
			int carry = 0;
			unsigned int	sub;

			if (val.intValPtr[size - 1] < 0)
			{
				sign = -1;
				for (; i < size; i++)
					val.intValPtr[i] *= -1;
				for (i = 0; i < _val.size; i++)
					_val.val.intValPtr[i] *= -1;
			}
			for (i = 0; i < size && i < _val.size; i++)
			{
				sub = val.intValPtr[i] - _val.val.intValPtr[i] + carry;
				carry = sub / kIntLimit;
				val.intValPtr[i] = sub % kIntLimit;
			}
			for (; i < size; i++)
			{
				sub = val.intValPtr[i] + carry;
				carry = sub / kIntLimit;
				val.intValPtr[i] = sub % kIntLimit;
			}
			for (; i < _val.size; i++)
			{
				sub = -1 * _val.val.intValPtr[i] + carry;
				carry = sub / kIntLimit;
				pushBack((int)(sub % kIntLimit));
			}
			if (carry != 0)
				pushBack(carry);
			if (sign == -1)
			{
				for (i = 0; i < size; i++)
					val.intValPtr[i] *= -1;
				for (i = 0; i < _val.size; i++)
					_val.val.intValPtr[i] *= -1;
			}
		}
	}

	return	*this;
}

bool	ExRange::operator==(ExRange& _val)
{
	if (!isInt)
	{

	}
	else
	{
		if (size != _val.size)
			return	false;
		else
		{
			size_t	i = 0;

			for (i = size - 1; i > 0; i--)
			{
				if (val.intValPtr[i] != _val.val.intValPtr[i])
					return false;
			}
			if (val.intValPtr[i] != _val.val.intValPtr[i])
				return	false;
		}
	}
	
	return	true;
}

bool	ExRange::operator!=(ExRange& _val)
{
	if (!isInt)
	{

	}
	else
	{
		if (size != _val.size)
			return	true;
		else
		{
			size_t i = 0;

			for (i = size - 1; i > 0; i--)
			{
				if (val.intValPtr[i] == _val.val.intValPtr[i])
					return	false;
			}
			if (val.intValPtr[i] == _val.val.intValPtr[i])
				return false;
		}
	}

	return	true;
}

bool	ExRange::operator>=(ExRange& _val)
{

}

bool	ExRange::operator<=(ExRange& _val)
{

}

bool	ExRange::operator>(ExRange& _val)
{

}

bool	ExRange::operator<(ExRange& _val)
{

}