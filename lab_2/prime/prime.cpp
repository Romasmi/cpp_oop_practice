#include "pch.h"

#include "prime.h"

using namespace std;

bool IsEven(const size_t number)
{
	return number % 2 == 0;
}

PrimeSet GeneratePrimeNumbersSet(const int upperBound)
{
	PrimeSet primeSet;
	vector<bool> primeVector(upperBound + 1);
	if (upperBound >= 1)
	{
		primeSet.insert(1);
	}
	fill(primeVector.begin(), primeVector.end(), true);

	if (upperBound >= 2)
	{
		primeSet.insert(2);
	}

	for (unsigned int i = 3; i <= upperBound; i += 2)
	{
		if (!primeVector[i])
		{
			continue;
		}
		primeSet.insert(i);
		for (unsigned int j = i * i; j <= upperBound; i += 2)
		{
			if (!primeVector[j])
			{
				continue;
			}

			if (j % i == 0)
			{
				primeVector[j] = false;
			}
		}
	}
	return primeSet;
}