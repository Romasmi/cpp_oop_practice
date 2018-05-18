#include "stdafx.h"
#include "html_processor.h"
#include <algorithm>
using namespace std;

const pair<string, string> HTML_ENTITY_NAME[]{
	{ "\"", "&quot;" },
	{ "\'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "&", "&amp;" }
};

string StringReplace(const string& line, const string& search, const string& replace)
{
	string newString(line);
	size_t position = newString.find(search, 0);
	while (position != string::npos)
	{
		newString.replace(position, search.length(), replace);
		position += replace.length();
		position = newString.find(search, position);
	}
	return newString;
}

string HtmlDecode(const string& html)
{
	string decodedHtml(html);

	for (auto& htmlEntity : HTML_ENTITY_NAME)
	{
		decodedHtml = StringReplace(decodedHtml, htmlEntity.second, htmlEntity.first);
	}
	return decodedHtml;
}

string HtmlEncode(const string& html)
{
	string encodedHtml(html);

	for (auto& htmlEntity : HTML_ENTITY_NAME)
	{
		encodedHtml = StringReplace(encodedHtml, htmlEntity.first, htmlEntity.second);
	}
	return encodedHtml;
}

void HtmlDecode(istream& input, ostream& output)
{
	string currentLine;
	while (getline(cin, currentLine))
	{
		output << HtmlDecode(currentLine) << "\n";
	}
}

void HtmlEncode(istream& input, ostream& output)
{
	string currentLine;
	while (getline(cin, currentLine))
	{
		output << HtmlEncode(currentLine) << "\n";
	}
}
