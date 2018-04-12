#include "stdafx.h"
#include <limits>
using namespace std;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const char MIN_LETTER = 'A';
const char MAX_LETTER = 'Z';

unsigned int LetterToNumber(const unsigned char letter)
{
	return (letter >= '0' && letter <= '9') ? static_cast<int>(letter - '0') : static_cast<int>(letter) - 55;
}

char NumberToLetter(const unsigned int number)
{
	return (number >= 0 && number <= 9) ? static_cast<char>(number + '0') : static_cast<char>(number + 55);
}

bool IsAllowableLetter(const unsigned char letter)
{
	return letter >= MIN_LETTER && letter <= MAX_LETTER;
}

bool IsAllowableRadix(const unsigned int radix)
{
	return radix >= MIN_RADIX && radix <= MAX_RADIX;
}

bool IsNegativeNumber(const string& number)
{
	return number.length() && number[0] == '-';
}

unsigned int StringToInt(const string& str, const unsigned int radix, bool& wasError)
{
	unsigned int number = 0;

	if (radix == 10)
	{
		return stoi(str);
	}

	for (int i = str.length() - 1, discharge = 0; i >= 0; --i, ++discharge)
	{
		unsigned int currentDischargeNumber = LetterToNumber(str[i]);
		if (currentDischargeNumber > radix)
		{
			wasError = true;
			return 0;
		}

		if (!wasError)
		{
			number += currentDischargeNumber * pow(radix, discharge);
		}
		else
		{
			return 0;
		}
	}
	return number;
}

string IntToString(unsigned int n, const unsigned int radix, bool& wasError)
{
	if (radix == 0)
	{
		wasError = true;
		return "";
	}

	string number = "";
	while (n != 0)
	{
		int remainder = n % radix;
		n = n / radix;
		number = NumberToLetter(remainder) + number;
	}
	return number;
}

string Convert(const int startRadix, const int finishRadix, const string& number, bool& wasError)
{
	bool isNeganiveNumber = IsNegativeNumber(number);
	int decimalNumber;
	if (isNeganiveNumber)
	{
		decimalNumber = StringToInt(number.substr(1), startRadix, wasError);
	}
	else
	{
		decimalNumber = StringToInt(number, startRadix, wasError);
	}

	string newNumber;
	if (!wasError)
	{
		string finalNumber = IntToString(decimalNumber, finishRadix, wasError);
		return isNeganiveNumber ? '-' + finalNumber : finalNumber;
	}
	else
	{
		return "";
	}
}

bool IsValidRadix(const string& number, const unsigned int radix)
{
	unsigned int i = IsNegativeNumber(number) ? 1 : 0;
	for (i; i < number.length(); ++i)
	{
		if (!(LetterToNumber(number[i]) < radix))
		{
			return false;
		}
	}
	return true;
}

bool IsValidated(const unsigned int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Invaid parameters count" << endl;
		return false;
	}

	unsigned int startRadix;
	unsigned int finishRadix;
	try
	{
		startRadix = stoi(argv[1]);
		finishRadix = stoi(argv[2]);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}

	if (!IsAllowableRadix(startRadix) || !IsAllowableRadix(finishRadix))
	{
		cout << "Not allowable radix" << endl;
		return false;
	}

	const string number = static_cast<string>(argv[3]);
	if (number == "")
	{
		cout << "Empty input number" << endl;
		return false;
	}

	if (!IsValidRadix(number, startRadix))
	{
		cout << "Non conformity of input radix and input number" << endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (!IsValidated(argc, argv))
	{
		return 1;
	}

	bool wasError = false;
	string newNumber = Convert(stoi(argv[1]), stoi(argv[2]), argv[3], wasError);

	if (!wasError)
	{
		cout << newNumber << '\n';
		return 0;
	}
	else
	{
		return 1;
	}
}
