#include "stdafx.h"
using namespace std;
using MatrixRow = vector<double>;

struct Matrix
{
	size_t rowsCount;
	size_t colsCount;
	double determinant;
	vector<MatrixRow> values;
};


bool IsEven(const int number)
{
	return number % 2 == 0;
}

double GetDiagonalComposition(const Matrix& matrix)
{
	double result = matrix.values[0][0];
	for (unsigned int i = 1; i < matrix.rowsCount; ++i)
	{
		result *= matrix.values[i][i];
	}
	return result;
}

void ProccessColumnForGaussMethod(Matrix& matrix, const unsigned int startRow)
{
	for (unsigned int i = startRow + 1; i < matrix.rowsCount; ++i)
	{
		if (matrix.values[i][startRow] != 0)
		{
			swap(matrix.values[startRow], matrix.values[i]);
		}
	}
}

void FetchSubdiagonalColumnNumbersToZero(Matrix& matrix, const unsigned int column)
{
	for (unsigned int j = column + 1; j < matrix.rowsCount; ++j)
	{
		if (matrix.values[j][column] != 0)
		{
			MatrixRow subsidiaryRow = matrix.values[column];
			const double delimiter = matrix.values[column][column];
			const double factor = matrix.values[j][column];

			for (int k = 0; k < matrix.colsCount; ++k)
			{
				matrix.values[j][k] -= subsidiaryRow[k] / delimiter * factor;
			}
		}
	}
}

double GetDeterminant(const Matrix& matrix)
{
	Matrix helpMatrix(matrix);
	for (unsigned int i = 0; i < helpMatrix.colsCount - 1; ++i)
	{
		if (helpMatrix.values[i][i] == 0)
		{
			ProccessColumnForGaussMethod(helpMatrix, i);
		}

		if (helpMatrix.values[i][i] == 0)
		{
			return 0;
		}
		FetchSubdiagonalColumnNumbersToZero(helpMatrix, i);
	}
	return GetDiagonalComposition(helpMatrix);
}

bool SetMatrix(istream& input, Matrix& matrix)
{
	string currentLine;
	try
	{
		while (getline(input, currentLine))	
		{
			std::istringstream stringIterator(currentLine);
			matrix.values.push_back(MatrixRow(istream_iterator<double>(stringIterator), istream_iterator<double>()));

			if (matrix.values.front().size() != matrix.values.back().size())
			{
				return false;
			}
		}
		matrix.rowsCount = matrix.values.size();

		if (matrix.rowsCount == 0 || matrix.values[0].size() == 1)
		{ 
			return false;
		}
		matrix.colsCount = matrix.values.front().size();
		 
		return true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

bool SetMatrixFromFile(const string& filename, Matrix& matrix)
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

Matrix GetSubMatrix(const Matrix& matrix, const unsigned int cutRow, const unsigned int cutColumn)
{
	Matrix subMatrix;
	for (unsigned int i = 0; i < matrix.rowsCount; ++i)
	{
		MatrixRow subRow;
		for (unsigned int j = 0; j < matrix.colsCount; ++j)
		{
			if (i != cutRow && j != cutColumn)
			{
				subRow.push_back(matrix.values[i][j]);
			}
		}
		if (subRow.size())
		{
			subMatrix.values.push_back(subRow);
		}
	}
	subMatrix.rowsCount = matrix.rowsCount - 1;
	subMatrix.colsCount = matrix.colsCount - 1;
	return subMatrix;
}

void PrintMatrix(Matrix& matrix)
{
	cout.precision(3);
	for (const MatrixRow row : matrix.values)
	{
		copy(row.begin(), row.end(), ostream_iterator<double>(cout, " "));
		cout << "\n";
	}
}

double GetMinorOfMatrix(const Matrix& matrix, const unsigned int row, const unsigned int column)
{
	Matrix subMatrix;
	subMatrix = GetSubMatrix(matrix, row, column);
	return GetDeterminant(subMatrix);
}

Matrix GetMinorMatrix(const Matrix& matrix)
{
	Matrix minorMatrix;
	minorMatrix.rowsCount = matrix.rowsCount;
	minorMatrix.colsCount = matrix.colsCount;
	for (unsigned int i = 0; i < matrix.rowsCount; ++i)
	{
		MatrixRow subRow;
		for (unsigned int j = 0; j < matrix.colsCount; ++j)
		{
			subRow.push_back(GetMinorOfMatrix(matrix, i, j));
		}
		minorMatrix.values.push_back(subRow);
	}
	return minorMatrix;
}

Matrix GetAlgebraicComplementMatrix(const Matrix& matrix)
{
	Matrix algebraicComplementMatrix;
	Matrix minorMatrix = GetMinorMatrix(matrix);
	algebraicComplementMatrix.colsCount = matrix.colsCount;
	algebraicComplementMatrix.rowsCount = matrix.rowsCount;

	for (unsigned int i = 0; i < matrix.rowsCount; ++i)
	{
		MatrixRow subRow;
		for (unsigned int j = 0; j < matrix.colsCount; ++j)
		{
			subRow.push_back(minorMatrix.values[i][j] * (IsEven(i + j) ? 1 : -1));
		}
		algebraicComplementMatrix.values.push_back(subRow);
	}
	return algebraicComplementMatrix;
}

void TransposeMatrix(Matrix& matrix)
{
	for (unsigned int i = 0; i < matrix.rowsCount - 1; ++i)
	{
		for (unsigned int j = i + 1; j < matrix.colsCount; ++j)
		{
			swap(matrix.values[i][j], matrix.values[j][i]);
		}
	}
}

void MultiplyMatrixByScalar(Matrix& matrix, const double scalar)
{
	Matrix multipliedMatrix;
	for_each(matrix.values.begin(), matrix.values.end(), [scalar](MatrixRow& row)
	{ 
		for_each(row.begin(), row.end(), [scalar](double& element)
		{
			element *= scalar;
		});
	});
}

bool InvertMatrix(Matrix& matrix)
{
	if (matrix.rowsCount != matrix.colsCount)
	{
		return false;
	}

	double determinant = GetDeterminant(matrix);
	if (matrix.determinant == 0)
	{
		return false;
	}
	matrix = GetAlgebraicComplementMatrix(matrix);
	TransposeMatrix(matrix);
	MultiplyMatrixByScalar(matrix, 1 / determinant);
	return true;
}

int main(const int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid parameters count" << endl;
		return 1;
	}

	Matrix matrix;
	if (!SetMatrixFromFile(argv[1], matrix))
	{
		return 1;
	}

	if (matrix.rowsCount != matrix.colsCount)
	{
		cout << "Matrix is't not regular." << endl;
		return 1;
	}

	if (InvertMatrix(matrix))
	{
		PrintMatrix(matrix);
		return 0;
	}
	else
	{
		cout << "It's impossible to find invert  matrix" << endl;
		return 1;
	}
}
