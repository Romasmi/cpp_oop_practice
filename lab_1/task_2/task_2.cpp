#include "stdafx.h"
using namespace std;

size_t SumDigits(size_t i)
{
	size_t sum = 0;

	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}

void Print(const vector<size_t>& vectorToPrint)
{
	for (size_t i = 0; i < vectorToPrint.size(); ++i)
	{
		cout << vectorToPrint[i] << '\n';
	}
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

	if (MAX < MIN || MIN < 1)
	{
		cout << "Error: please, follow next rules: MIN >= 1, MIN < MAX";
		return 1;
	}

	vector<size_t> digits;

	for (size_t i = MIN; i < MAX; ++i)
	{
		if (i % SumDigits(i) == 0)
		{
			digits.push_back(i);
		}
	}

	sort(digits.begin(), digits.end());
	Print(digits);
   
	return 0;
}

