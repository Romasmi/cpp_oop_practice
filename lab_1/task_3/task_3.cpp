#include "stdafx.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <math.h>
using namespace std;

struct Matrix2D
{
	size_t rowsCount;
	size_t colsCount;
	double definer;
	vector<vector<double>> values;
};

bool SetMatrix(istream& input, Matrix2D& matrix)
{
	string currentLine;
	try
	{
		while (getline(input, currentLine))
		{
			std::istringstream stringIterator(currentLine);
			matrix.values.push_back(vector<double>(istream_iterator<double>(stringIterator), istream_iterator<double>()));

			if (matrix.values.front().size() != matrix.values.back().size())
			{
				return false;
			}
		}
		matrix.rowsCount = matrix.values.size();
		matrix.colsCount = matrix.values.front().size();
		return true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

bool SetMatrixFromFile(const string& filename, Matrix2D& matrix)
{
	ifstream input;
	input.open(filename);

	if (!input.is_open())
	{
		cout << "Incorrect file" << endl;
		return false;
	}
	else if (SetMatrix(input, matrix))
	{
		return true;
	}
	else
	{
		cout << "Could't get matrix from file" << endl;
		return false;
	}
}

double GetGiagonalComposition(Matrix2D &matrix)
{
	double result = matrix.values[0][0];
	for (unsigned int i = 1; i < matrix.rowsCount; ++i)
	{
		result *= matrix.values[i][i];
	}
	return result;
}

void ProccessColumnForGaussMethod(Matrix2D &matrix, unsigned int startRow)
{
	for (unsigned int j = startRow + 1; j < matrix.rowsCount; ++j)
	{
		if (matrix.values[j][startRow] != 0)
		{
			swap(matrix.values[startRow], matrix.values[j]);
		}
	}
}

void FetchSubdiagonalColumnNumbersToZero(Matrix2D &matrix, unsigned int column)
{
	for (unsigned int j = column + 1; j < matrix.rowsCount; ++j)
	{
		if (matrix.values[j][column] != 0)
		{
			vector<double> subsidiaryRow = matrix.values[column];
			const double delimiter = matrix.values[column][column];
			const double factor = matrix.values[j][column];

			for (int k = 0; k < matrix.colsCount; ++k)
			{
				matrix.values[j][k] -= subsidiaryRow[k] / delimiter * factor;
			}
		}
	}
}

void SetDefiner(Matrix2D& matrix)
{
	Matrix2D helpMatrix(matrix);
	for (unsigned int i = 0; i < helpMatrix.colsCount - 1; ++i)
	{
		if (helpMatrix.values[i][i] == 0)
		{
			ProccessColumnForGaussMethod(helpMatrix, i);
		}

		if (helpMatrix.values[i][i] == 0)
		{
			matrix.definer = 0;
			return;
		}
		FetchSubdiagonalColumnNumbersToZero(helpMatrix, i);
	}

	matrix.definer = GetGiagonalComposition(helpMatrix);
}

bool InvertMatrix(Matrix2D& matrix)
{
	return false;
}

void Print2DVector(Matrix2D& matrix)
{
	vector<vector<double>>::iterator row;
	vector<double>::iterator col;
	for (row = matrix.values.begin(); row != matrix.values.end(); row++)
	{
		for (col = row->begin(); col != row->end(); col++)
		{
			cout << col[0] << ' ';
		}
		cout << "\n";
	}
}

int main(const int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid parameters count" << endl;
		return 1;
	}

	Matrix2D matrix;
	if (!SetMatrixFromFile(argv[1], matrix))
	{
		return 1;
	}

	if (matrix.rowsCount != matrix.colsCount)
	{
		cout << "Matrix is't not regular." << endl;
		return 1;
	}

	SetDefiner(matrix);
	cout << matrix.definer << endl;
	Print2DVector(matrix);
	return 0;
}
