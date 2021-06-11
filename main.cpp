#include	<iostream>
#include	<vector>
#include	<string>
#include	<thread>
#include	"Calc.h"
#include	"ExRange.h"


using namespace std;

int	parse(vector<string>& vParsedStr, const string& str);
int	parseCommand(const vector<string>& vParsedStr);
int	parseSyntax(values& vals, vector<char>& vOp, const string& str);
void	displayInformation(int errorCode);

struct defaultValue
{
	complexValue tempComplexVal;
	realValue tempRealVal;
	string	valStr;
	bool	isImaginaryVal = false;
	bool	isUnderDecPoint = false;
	int		sign = 1;
};

int main(int argc, char* argv[])
{
	while (true)
	{
		string	line;

		vector<string> vParsedStr;

		values vals;
		vector<char> vOp;

		complexValue	result;

		int code;

		if (argc == 1)
		{
			cout << " >>> ";
			cin >> line;
		}
		else if (argc == 2)
			line = string(argv[1]);
		code = parse(vParsedStr, line);
		if (code != 0)
		{
			displayInformation(code);
			continue;
		}
		code = parseCommand(vParsedStr);
		if (code != 0 && code != 1)
		{
			displayInformation(code);
			continue;
		}
		parseSyntax(vals, vOp, vParsedStr[0]);
		if (argc == 2 || code == 1)
			break;
	}

	return 0;
}

int parse(vector<string>& vParsedStr, const string& str)
{
	int	strNum = 0;

	vParsedStr.push_back("");
	for (unsigned i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			strNum++;
			vParsedStr.push_back("");
		}
		else
		{
			if (vParsedStr.size() < 3)
				vParsedStr[strNum] += str[i];
			else
				return 2;
		}
	}

	return	0;
};

int parseCommand(const vector<string>& vParsedStr)
{
	string sysCommand[3] = { "exit", "clearDisplay", "help" };
	string memCommand[6] = { "clearMem", "store", "insert", "modify", "delete", "ans" };

	if (vParsedStr[0] == sysCommand[0])
		return 1;
	else if (vParsedStr[0] == sysCommand[1])
		;
	else if (vParsedStr[0] == sysCommand[2])
	{
		cout << "Engine Command" << endl;
		cout << "exit : Exit the program, clearDisplay : clear display." << endl << endl;
		cout << "Memory Command" << endl;
		cout << "clearMem : Deletes the values stored in memory, store : Store value in memory";
	}
	else
	{
		
	}
	
	return	0;
};

void	displayInformation(int code)
{
	switch (code)
	{
	case 2:
		cout << "System error : Unknwon command." << endl;
		break;
	case 3:
		cout << "Syntax error : Lack of operands." << endl;
		break;
	case 4:
		cout << "Syntax error : Empty parenthesis" << endl;
		break;
	case 5:
		cout << "Syntax error : Unacceptable consecutive operators." << endl;
		break;
	case 6:
		cout << "Mathematical error : '%' operator cannot be used for real values." << endl;
		break;
	case 7:
		cout << "Mathematical error : Cannot be divided by zero." << endl;
	default:
		break;
	}
}

int parseSyntax(values& vals, vector<char>& vOp, const string& str)
{
	int leftParenthesisNum = 0, rightParenthesisNum = 0;

	defaultValue	defaultVal;

	char tempChar = 0;

	int	sign = 1;

	bool tempArithOp1 = false, tempArithOp2 = false;
	bool tempParenthesisOp = false;
	bool tempIsNumeric = false;
	bool arithOp1 = false, arithOp2 = false;
	bool parenthesisOp = false;
	bool isNumeric = false;

	for (unsigned int i = 0; i < str.size(); i++)
	{
		tempArithOp1 |= tempChar == '*' || tempChar == '/' || tempChar == '%';
		tempArithOp2 |= tempChar == '+' || tempChar == '-';
		tempParenthesisOp |= tempChar == '(' || tempChar == ')';
		tempIsNumeric |= tempChar >= '0' && tempChar <= '9';

		arithOp1 |= str[i] == '*' || str[i] == '/' || str[i] == '%';
		arithOp2 |= str[i] == '+' || str[i] == '-';
		parenthesisOp |= str[i] == '(' || str[i] == ')';
		isNumeric |= str[i] >= '0' && str[i] <= '9';

		if (tempChar == 0 && arithOp1)
			return 3;
		else if (tempArithOp1 && arithOp1)
			return 5;
		else if (tempArithOp2 && arithOp1)
			return 5;
		else if (tempChar == '(' || str[i] == ')')
			return 4;
		else if (tempChar == '(' && arithOp1 || tempChar == '(' && arithOp2)
			return 3;
		else if (str[i] == '(')
		{
			leftParenthesisNum++;
			vOp.push_back('(');
		}
		else if (str[i] == ')')
		{
			rightParenthesisNum++;
			vOp.push_back(')');
		}
		else if (tempIsNumeric && arithOp1)
		{
			vals.push_back(defaultVal.tempComplexVal);
			vOp.push_back(str[i]);
			if (defaultVal.isImaginaryVal)
			{
				if (defaultVal.isUnderDecPoint)
					defaultVal.tempComplexVal.imaginVal = ExRange::doubleEncode(defaultVal.valStr);
				else
					defaultVal.tempComplexVal.imaginVal = ExRange::intEncode(defaultVal.valStr);
			}
			else
			{
				if (defaultVal.isUnderDecPoint)
					defaultVal.tempComplexVal.realVal = defaultVal.tempRealVal = ExRange::doubleEncode(defaultVal.valStr);
				else
					defaultVal.tempComplexVal.realVal = defaultVal.tempRealVal = ExRange::intEncode(defaultVal.valStr);
			}
			defaultVal = defaultValue();
		}
		else if (tempIsNumeric && arithOp2)
		{
			vals.push_back(defaultVal.tempComplexVal);
			vOp.push_back(str[i]);
			if (defaultVal.isImaginaryVal)
			{
				if (defaultVal.isUnderDecPoint)
					defaultVal.tempComplexVal.imaginVal = ExRange::doubleEncode(defaultVal.valStr);
				else
					defaultVal.tempComplexVal.imaginVal = ExRange::intEncode(defaultVal.valStr);
			}
			else
			{
				if (defaultVal.isUnderDecPoint)
					defaultVal.tempComplexVal.realVal = defaultVal.tempRealVal = ExRange::doubleEncode(defaultVal.valStr);
				else
					defaultVal.tempComplexVal.realVal = defaultVal.tempRealVal = ExRange::intEncode(defaultVal.valStr);
			}
			defaultVal = defaultValue();
		}
		else if (tempArithOp1 && str[i] == '-' || tempArithOp2 && str[i] == '-')
			sign = -1;
		else if (isNumeric)
			defaultVal.valStr += str[i];
		else if (str[i] == '.')
			defaultVal.valStr += str[i];
		else if (tempIsNumeric && str[i] == 'i')
			defaultVal.isImaginaryVal = true;
		else if (tempChar == '.' && isNumeric)
			defaultVal.isUnderDecPoint = true;
		if (leftParenthesisNum < rightParenthesisNum)
			return 2;
	}

	return 0;
}

