#include "pch.h"
using namespace std;
using CryptFunction = function<void(uint8_t& byte, const uint8_t key)>;

struct Params
{
	string command;
	string inputFileName;
	string outputFileName;
	uint8_t key;
};

struct BytePosition
{
	uint8_t left;
	uint8_t right;
};

const unsigned int ARGS_COUNT = 5;
const uint8_t MIN_KEY = 0;
const uint8_t MAX_KEY = 255;
const vector<BytePosition> BYTE_POSITION = {
	{ 7, 5 },
	{ 6, 1 },
	{ 5, 0 },
	{ 4, 7 },
	{ 3, 6 },
	{ 2, 4 },
	{ 1, 3 },
	{ 0, 2 }
};

template <class T>
bool Between(T item, T min, T max)
{
	return item >= min && item <= max;
}

void CopyBit(const uint8_t sourceByte, uint8_t& destinationByte, const uint8_t sourcePos, const uint8_t desctinationPos)
{
	uint8_t mask = 0x1;
	mask = (mask & (sourceByte >> sourcePos)) << desctinationPos;
	destinationByte = destinationByte | mask;
}

void Encrypt(uint8_t& byte, const uint8_t key)
{
	uint8_t processedByte = 0;
	byte = byte ^ key;
	for (const BytePosition& position : BYTE_POSITION)
	{
		CopyBit(byte, processedByte, position.left, position.right);
	}
	byte = processedByte;
}

void Decrypt(uint8_t& byte, const uint8_t key)
{
	uint8_t processedByte = 0;
	for (const BytePosition& position : BYTE_POSITION)
	{
		CopyBit(byte, processedByte, position.right, position.left);
	}
	byte = processedByte;
	byte = byte ^ key;
}

const pair<string, CryptFunction> COMMAND_TO_CRYPT_FUNCTION[] = {
	{ "crypt", Encrypt },
	{ "decrypt", Decrypt },
};

CryptFunction CommandToCryptFunction(const string& command)
{
	for (auto& p : COMMAND_TO_CRYPT_FUNCTION)
	{
		if (p.first == command)
		{
			return p.second;
		}
	}
	return nullptr;
}

void Crypt(istream& in, ostream& out, const uint8_t key, const CryptFunction& cryptFunction)
{
	char byte;
	while (in.get(byte))
	{
		uint8_t b = static_cast<uint8_t>(byte);
		cryptFunction(b, key);
		out.put(b);
	}
}

bool Crypt(
	const string& inputFileName,
	const string& outputFileName,
	const uint8_t key,
	const CryptFunction& cryptFunction)
{
	ifstream infile(inputFileName, ios_base::in | ios_base::binary);
	ofstream outile(outputFileName, ios_base::out | ios_base::binary);

	if (!(infile.is_open() && outile.is_open()))
	{
		return false;
	}
	Crypt(infile, outile, key, cryptFunction);
	return true;
}

bool ParseCommandLine(int argc, char* argv[], Params& params)
{
	if (argc != ARGS_COUNT)
	{
		return false;
	}

	params.command = argv[1];
	params.inputFileName = argv[2];
	params.outputFileName = argv[3];
	if (CommandToCryptFunction(params.command) == nullptr)
	{
		return false;
	}

	try
	{
		params.key = static_cast<uint8_t>(stoul(argv[4]));
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return false;
	}

	return Between<uint8_t>(params.key, MIN_KEY, MAX_KEY);
}

int main(int argc, char* argv[])
{
	Params params;
	if (!ParseCommandLine(argc, argv, params))
	{
		cout << "Invalid params."
			 << "Correct params: crypt.txt <crypt way: encrypt|decrypt> <input_file> <output_file> <key from 0 to 255>\n";
		return 1;
	}

	CryptFunction cryptFunction = CommandToCryptFunction(params.command);
	return Crypt(params.inputFileName, params.outputFileName, params.key, cryptFunction) ? 0 : 1;
}
