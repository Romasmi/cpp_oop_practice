#include "stdafx.h"
using namespace std;

bool IsEven(const int number)
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

	const int MIN = atoi(argv[1]);
	const int MAX = atoi(argv[2]);

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

	int i = MAX;
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
