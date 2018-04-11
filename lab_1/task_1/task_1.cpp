#include "stdafx.h"
using namespace std;

string StringReplace(const string& line, const string& search, const string& replace)
{
	string newLine;
	size_t currentPosition = 0;
	size_t searchLength = search.length();
	size_t lineLength = line.length();
	while (currentPosition + searchLength < lineLength)
	{
		if (line.compare(currentPosition, searchLength, search) == 0)
		{
			newLine += replace;
			currentPosition += searchLength;
		}
		else
		{
			newLine += line[currentPosition];
			++currentPosition;
		}
	}
	if (lineLength - currentPosition > 0)
	{
		newLine += line.substr(currentPosition, lineLength - currentPosition);
	}
	return newLine;
}

void CopyByReplacing(istream& input, ostream& output, const string& search,
	const string& replace)
{
	string currentLine;
	if (search != "")
	{
		while (getline(input, currentLine))
		{
			const string newLine = StringReplace(currentLine, search, replace);
			output << newLine << '\n';
		}
	}
	else
	{
		while (getline(input, currentLine))
		{
			output << currentLine << '\n';
		}
	}
}

bool CopyFileByReplacing(const string& inputFilename, const string& outputFilname, const string& search,
	const string& replace)
{
	ifstream input;
	input.open(inputFilename);
	ofstream output;
	output.open(outputFilname);

	if (!input.is_open() || !output.is_open())
	{
		cout << "File(s) incorrect" << endl;
		return false;
	}

	CopyByReplacing(input, output, search, replace);
}

int main(const int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid parameter`s count" << endl;
		return 1;
	}

	if (argv[3] == "")
	{
		cout << "Input search string have not to be empty" << endl;
		return 1;
	}
	 
	if (!CopyFileByReplacing(argv[1], argv[2], argv[3], argv[4]))
	{
		return 1;
	}
	return 0;
}
