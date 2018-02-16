#include "stdafx.h"
using namespace std;

bool IsEven(const size_t number)
{
	return number % 2 == 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid parameters count \n";
		return 1;
	}

	const size_t MIN = stoi(argv[1]);
	const size_t MAX = stoi(argv[2]);

	if (MAX < MIN)
	{
		cout << "MAX have to be more than MIN";
		return 1;
	}

	if (IsEven(MAX))
	{
		cout << MAX;
	}
	else if (MAX > MIN + 1)
	{
		cout << MAX - 1;
	}
	else
	{
		cout << "There are not even numbers";
		return 0;
	}

	size_t i = MAX - 1;
	do
	{
		--i;
		if (IsEven(i))
		{
			cout << ", " << i;
		}
	} while (i > MIN);

	cout << endl;

	return 0;
}
