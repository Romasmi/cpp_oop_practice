#include "stdafx.h"
#include "vector.h"
using namespace std;

int main()
{
	BaseVector numberVector;
	SetVectorFromStream(numberVector, cin);
	try
	{
		ProcessVector(numberVector);
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
		return 1;
	}
	sort(numberVector.begin(), numberVector.end());
	PrintVector(numberVector);
	return 0;
}