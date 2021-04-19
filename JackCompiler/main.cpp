#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

#include "JackTokens.hpp"
#include "StringSplitter.hpp"
#include "XmlCompilationEngine.hpp"


//see https://stackoverflow.com/questions/50668814/vs2017-e0135-namespace-std-has-no-member-filesystem
//for forcing C++ 17 in VS 2019
namespace fs = std::filesystem;
using namespace std;

string removeQuotes(string in)
{
	istringstream input{ in };
	ostringstream output{};
	while (input.good() == true)
	{
		char temp;
		input >> temp;
		if (temp != '"')
		{
			output << temp;
		}
	}
	return output.str();
}

string sanitize(string in)
{
	istringstream input{ in };
	ostringstream output{};
	while (input.good() == true)
	{
		char temp;
		input >> temp;
		if (temp == '/' || temp == '\\')
		{
			output << '.';
		}
		else
		{
			output << temp;
		}
	}
	return output.str();
}

int main(int argc, char* argv[])
{
	vector<string> files_to_process{};
#ifdef _DEBUG
	//makes debugging easier by allowing you to directly load in files w/o using command line
	files_to_process.push_back("tests/ch10/ArrayTest/Main.jack");
	//files_to_process.push_back("tests/ch10/ExpressionLessSquare/Square.jack");
	//files_to_process.push_back("tests/ch10/ExpressionLessSquare/SquareGame.jack");
	ofstream output_file{ "Seven.xml" };

#else
	ofstream output_file{};
	ofstream xml_file{};
	string output_file_name = "";

	if (argc != 2)
	{
		cout << "Usage: PROGRAM.EXE <FILE.JACK | DIRECTORY>" << endl;
		return -1;
	}
	auto pieces = StringSplitter::split(argv[1], ".");
	if (pieces.size() == 1)
	{
		//directory
		output_file_name = argv[1];
		for (auto item : fs::directory_iterator(output_file_name))
		{
			if (fs::is_directory(item.path()) == false)
			{
				ostringstream temp;
				temp << item.path().filename();
				string current_file = removeQuotes(temp.str());

				auto file_pieces = StringSplitter::split(current_file, ".");
				if (file_pieces.size() == 2 && file_pieces[1] == "jack")
				{
					temp = ostringstream{};
					temp << argv[1] << "/" << current_file;
					files_to_process.push_back(temp.str());
				}
			}
		}
	}
	else if (pieces.size() == 2)
	{
		files_to_process.push_back(argv[1]);
	}
	else
	{
		cout << "Unexpected file name: " << argv[1] << endl;
		return -1;
	}


	//file
	output_file_name = pieces[0];

	output_file_name += ".vm";
	string xml_file_name = pieces[0];
	xml_file_name += ".xml";
	output_file.open(output_file_name);
	xml_file.open(xml_file_name);
#endif // DEBUG

	for (auto file : files_to_process)
	{
		vector<JackToken*> tokens{};
		JackTokenizer tokenizer{ file };
		vector<vector<string>> program = tokenizer.processFile();
		JackTokenFactory* factory = JackTokenFactory::getInstance();

		for (auto line : program)
		{
			for (auto token_string : line)
			{
				JackToken* token = factory->tokenFromString(token_string);
				tokens.push_back(token);
			}
		}

		auto file_pieces = StringSplitter::split(file, ".");
		ofstream xml_file{ file_pieces[0] + ".xml" };
		XmlCompilationEngine ce{ tokens };
		ce.compile();
		xml_file << ce.toString();
		xml_file.close();
	}


	output_file.close();
	
}